const int plantPin = 7;
const int potPin = A1;                 // 滑动变阻器连接的接口
const int timeWaterOn = 30;            // 浇水时间，单位：秒
const int timeWaterOff = 30;           // 停止浇水时间，单位：秒
const int totalDayTime = 24 * 60 * 60; // 一天的总时间，单位：秒

int wateringTimes = 0;            // 一天浇水次数
int previousPotValue = -1;        // 上一次读取的滑动变阻器的值
int timeDelayBetweenWatering = 0; // 两次浇水之间的延迟

void setup()
{
  Serial.begin(9600);
  pinMode(plantPin, OUTPUT);
  pinMode(potPin, INPUT);
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
  timeDelayBetweenWatering = (totalDayTime / wateringTimes) - (timeWaterOn + timeWaterOff) * 4; // 计算两次浇水之间的延迟时间
  Serial.print("Updated Watering Times: ");
  Serial.println(wateringTimes);
  Serial.print("Time Delay Between Watering: ");
  Serial.print(timeDelayBetweenWatering / 3600.0, 2); // 将延迟时间以小时为单位打印，并保留两位小数
  Serial.println(" hours");
}

void delaySecondsWithPotCheck(int seconds)
{
  for (int i = 0; i < seconds; i++)
  {
    int potValue = analogRead(potPin);
    int actualPotValue = 1023 - potValue;
    Serial.print("Current Potentiometer Value: ");
    Serial.println(actualPotValue);
    if (actualPotValue / 100 != previousPotValue / 100)
    { // 检查百位数是否变化
      previousPotValue = actualPotValue;
      Serial.println("Potentiometer value changed, aborting watering.");
      updateWateringTimes();
      return; // 终止当前浇水
    }
    delay(1000); // 延时1秒
  }
}

void wateringCycle()
{
  for (int i = 0; i < 4; i++)
  {
    digitalWrite(plantPin, LOW);
    Serial.println("LOW-ON");
    delaySecondsWithPotCheck(timeWaterOn);

    digitalWrite(plantPin, HIGH);
    Serial.println("HIGH-OFF");
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
    Serial.println("HIGH-OFF");

    // 在下一次循环之前进行一天的延时
    delaySecondsWithPotCheck(totalDayTime - wateringTimes * (timeWaterOn + timeWaterOff) * 4);
  }
}