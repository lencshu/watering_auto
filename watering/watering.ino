const int plantPin = 7;
const int timeDelayUnit = 35; // 单次浇水时间，单位：秒
const int timeDelayOff4h = 60 * 60 * 4; // 浇水间隔时间4小时，单位：秒

void setup() {
  Serial.begin(9600);
  pinMode(plantPin, OUTPUT);
}

void delaySeconds(int seconds) {
  Serial.println(nbSecond);
  for (int i = 0; i < seconds; i++) {
    delay(1000); // 延时1秒
  }
}

void wateringCycle() {
  digitalWrite(plantPin, LOW);
  Serial.println("LOW-ON");
  delaySeconds(timeDelayUnit);

  digitalWrite(plantPin, HIGH);
  Serial.println("HIGH-OFF");
  delaySeconds(timeDelayUnit);
}

void loop() {
  for (int i = 0; i < 4; i++) {
    wateringCycle();
  }

  digitalWrite(plantPin, HIGH); // 确保浇水结束后保持关闭
  Serial.println("HIGH-OFF");

  // 总共延时20小时，分为5个4小时
  for (int i = 0; i < 5; i++) {
    delaySeconds(timeDelayOff4h);
  }
}