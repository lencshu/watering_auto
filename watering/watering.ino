const int plantPin = 7;
const int potPin = A1; // 滑动变阻器连接的接口
const int timeDelayUnit = 35; // 单次浇水时间，单位：秒
const int timeDelayOff4h = 60 * 60 * 4; // 浇水间隔时间4小时，单位：秒

int wateringTimes = 0; // 一天浇水次数
int previousPotValue = -1; // 上一次读取的滑动变阻器的值

void setup() {
  Serial.begin(9600);
  pinMode(plantPin, OUTPUT);
  pinMode(potPin, INPUT);
  updateWateringTimes(); // 初始化浇水次数
}

void updateWateringTimes() {
  int potValue = analogRead(potPin);
  int actualPotValue = 1023 - potValue;
  wateringTimes = (actualPotValue / 100) % 10; // 取百位数作为浇水次数
  Serial.print("Updated Watering Times: ");
  Serial.println(wateringTimes);
}

void delaySecondsWithPotCheck(int seconds) {
  for (int i = 0; i < seconds; i++) {
    int potValue = analogRead(potPin);
    int actualPotValue = 1023 - potValue;
    Serial.print("Current Potentiometer Value: ");
    Serial.println(actualPotValue);
    if (actualPotValue / 100 != previousPotValue / 100) { // 检查百位数是否变化
      previousPotValue = actualPotValue;
      Serial.println("Potentiometer value changed, aborting watering.");
      updateWateringTimes();
      return; // 终止当前浇水
    }
    delay(1000); // 延时1秒
  }
}

void wateringCycle() {
  digitalWrite(plantPin, LOW);
  Serial.println("LOW-ON");
  delaySecondsWithPotCheck(timeDelayUnit);
  
  digitalWrite(plantPin, HIGH);
  Serial.println("HIGH-OFF");
  delaySecondsWithPotCheck(timeDelayUnit);
}

void loop() {
  for (int i = 0; i < wateringTimes; i++) {
    wateringCycle();
  }

  digitalWrite(plantPin, HIGH); // 确保浇水结束后保持关闭
  Serial.println("HIGH-OFF");

  // 总共延时20小时，分为5个4小时
  for (int i = 0; i < 5; i++) {
    delaySecondsWithPotCheck(timeDelayOff4h);
  }
}