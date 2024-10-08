int plantPin = 7;
// 连续浇水时间 30s on 10s off
int timeDelayUnitOn = 30 * 1;
int timeDelayUnitOff = 10 * 1;
// 浇水间隔单位时间4h
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

void delayBySecond(int nbSecond)
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
  delayBySecond(timeDelayUnitOn);
  digitalWrite(plantPin, HIGH);
  Serial.println("HIGH-OFF");
  delayBySecond(timeDelayUnitOff);
}

void loop()
{
  //   int SensorValue = analogRead(A5);
  //   if(SensorValue >= 500)
  //   {
  wateringUnit();
  wateringUnit();
  // wateringUnit();
  // wateringUnit();
  // Serial.print("LOW-ON ");
  // Serial.print("HIGH-OFF ");
  Serial.println("HIGH-OFF");
  digitalWrite(plantPin, HIGH);
// 浇水间隔 4h * 5
  delayBySecond(timeDelayOff4h);
  delayBySecond(timeDelayOff4h);
  delayBySecond(timeDelayOff4h);
  delayBySecond(timeDelayOff4h);
  delayBySecond(timeDelayOff4h);
  //   }
}
