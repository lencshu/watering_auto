const int plantPin = 7;
const int potPin = A1;                     // 滑动变阻器连接的接口
const long timeWaterOn = 30;               // 浇水时间，单位：秒
const long timeWaterOff = 30;              // 停止浇水时间，单位：秒
const int cyclesPerWatering = 4;           // 每次浇水的循环次数
const long totalDayTime = 24L * 60L * 60L; // 一天的总时间，单位：秒，使用 L 后缀确保常量被正确处理为 long 类型

int wateringTimes = 0;             // 一天浇水次数
int previousPotValue = -1;         // 上一次读取的滑动变阻器的值
long timeDelayBetweenWatering = 0; // 两次浇水之间的延迟
String currentState = "HIGH-OFF";  // 当前浇水状态
bool debug = false;                // 调试开关

void setup()
{
  Serial.begin(9600);
  pinMode(plantPin, OUTPUT);
  pinMode(potPin, INPUT);

  // 检测串口监视器是否打开
  unsigned long start = millis();
  while (!Serial && (millis() - start < 5000))
  {
    // 等待5秒查看串口监视器是否打开
  }

  if (Serial)
  {
    debug = true; // 如果串口监视器打开，启用调试打印
    Serial.println("Serial monitor detected, debugging enabled.");
  }
  else
  {
    debug = false; // 如果串口监视器未打开，禁用调试打印
  }

  updateWateringTimes(); // 初始化浇水次数
}

void updateWateringTimes()
{
  int potValue = analogRead(potPin);
  int actualPotValue = 1023 - potValue;
  wateringTimes = (actualPotValue / 100) % 10; // 取百位数作为浇水次数
  if (wateringTimes == 0)
  {
    wateringTimes = 1; // 防止浇水次数为0
  }

  // 每次浇水单位的总时间（包含四次30秒的浇水和30秒的停止）
  long totalWateringUnitTime = (timeWaterOn + timeWaterOff) * cyclesPerWatering;
  // 计算总的浇水时间
  long totalWateringTime = totalWateringUnitTime * wateringTimes;
  // 计算每次浇水单位之间的延迟时间
  timeDelayBetweenWatering = (totalDayTime - totalWateringTime) / wateringTimes;

  if (debug)
  {
    Serial.print("Updated Watering Times: ");
    Serial.println(wateringTimes);
    Serial.print("Total Day Time (s): ");
    Serial.println(totalDayTime);
    Serial.print("Total Watering Unit Time (s): ");
    Serial.println(totalWateringUnitTime);
    Serial.print("Total Watering Time (s): ");
    Serial.println(totalWateringTime);
    Serial.print("Time Delay Between Watering (s): ");
    Serial.println(timeDelayBetweenWatering);
    Serial.print("Time Delay Between Watering (hours): ");
    Serial.print(timeDelayBetweenWatering / 3600.0, 2); // 将延迟时间以小时为单位打印，并保留两位小数
    Serial.println(" hours");
  }
}

void delaySecondsWithPotCheck(long seconds)
{
  for (long i = 0; i < seconds; i++)
  {
    int potValue = analogRead(potPin);
    int actualPotValue = 1023 - potValue;
    if (debug)
    {
      Serial.print("Current Potentiometer Value: ");
      Serial.print(actualPotValue);
      Serial.print(" - ");
      Serial.print(currentState);
      Serial.print(" - Watering Times: ");
      Serial.print(wateringTimes);
      Serial.print(" - Time Delay Between Watering: ");
      Serial.print(timeDelayBetweenWatering / 3600.0, 2); // 以小时为单位打印，并保留两位小数
      Serial.println(" hours");
    }
    if (actualPotValue / 100 != previousPotValue / 100)
    { // 检查百位数是否变化
      previousPotValue = actualPotValue;
      if (debug)
      {
        Serial.println("Potentiometer value changed, aborting watering.");
      }
      updateWateringTimes();
      return; // 终止当前浇水
    }
    delay(1000); // 延时1秒
  }
}

void wateringCycle()
{
  for (int i = 0; i < cyclesPerWatering; i++)
  {
    digitalWrite(plantPin, LOW);
    currentState = "LOW-ON";
    if (debug)
    {
      Serial.println(currentState);
    }
    delaySecondsWithPotCheck(timeWaterOn);

    digitalWrite(plantPin, HIGH);
    currentState = "HIGH-OFF";
    if (debug)
    {
      Serial.println(currentState);
    }
    delaySecondsWithPotCheck(timeWaterOff);
  }
}

void loop()
{
  while (true)
  { // 无限循环，每天执行一次浇水周期
    for (int i = 0; i < wateringTimes; i++)
    {
      wateringCycle();
      if (i < wateringTimes - 1)
      { // 如果不是最后一次浇水，进行延时
        delaySecondsWithPotCheck(timeDelayBetweenWatering);
      }
    }

    digitalWrite(plantPin, HIGH); // 确保浇水结束后保持关闭
    currentState = "HIGH-OFF";
    if (debug)
    {
      Serial.println(currentState);
    }

    // 在下一次循环之前进行一天的延时
    delaySecondsWithPotCheck(timeDelayBetweenWatering);
  }
}