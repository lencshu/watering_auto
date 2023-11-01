int plantPin = 7;
// 连续浇水时间
int timeDelayUnit = 35 * 1;
// 浇水间隔时间20h
int timeDelayOff4h = 60 * 60 * 4;
// int timeDelayOn = 1000 * 60 * 60 * 3;
// int timeDelayOff = 1000 * 60 * 20;
void setup()
{
  Serial.begin(9600);
  //   pinMode(A5, INPUT);
  pinMode(plantPin, OUTPUT);
  // while (!Serial)
  //   ;
  // Serial.println("start ");
}

void delay1s(int nbSecond)
{
  Serial.println(nbSecond);
  // for (int count = 0; count < timeDelayOn; count++)
  for (int count = 0; count < nbSecond; count++)
  {
    delay(1000);
  }
}

void wateringUnit()
{
  digitalWrite(plantPin, LOW);
  Serial.println("LOW-ON");
  delay1s(timeDelayUnit);
  digitalWrite(plantPin, HIGH);
  Serial.println("HIGH-OFF");
  delay1s(timeDelayUnit);
}

void loop()
{
  //   int SensorValue = analogRead(A5);
  //   if(SensorValue >= 500)
  //   {
  wateringUnit();
  wateringUnit();
  wateringUnit();
  wateringUnit();
  // Serial.print("LOW-ON ");
  // Serial.print("HIGH-OFF ");
  Serial.println("HIGH-OFF");
  digitalWrite(plantPin, HIGH);
  delay1s(timeDelayOff4h);
  delay1s(timeDelayOff4h);
  delay1s(timeDelayOff4h);
  delay1s(timeDelayOff4h);
  delay1s(timeDelayOff4h);
  //   }
}
