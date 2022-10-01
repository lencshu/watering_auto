int plantPin = 7;
int timeDelayUnit = 30 * 1;
int timeDelayOff = 60 * 60 * 8;
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

void delayCustom(int duration)
{
  // for (int count = 0; count < timeDelayOn; count++)
  for (int count = 0; count < duration; count++)
  {
    delay(1000);
  }
}

void wateringUnit()
{
  digitalWrite(plantPin, LOW);
  delayCustom(timeDelayUnit);
  digitalWrite(plantPin, HIGH);
  delayCustom(timeDelayUnit);
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
  digitalWrite(plantPin, HIGH);
  delayCustom(timeDelayOff);
  //   }
}
