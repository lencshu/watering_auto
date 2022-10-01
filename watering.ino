int plantPin = 7;
int timeDelayUnit = 25 * 1;
int timeDelayOff8h = 60 * 60 * 8;
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
  // for (int count = 0; count < timeDelayOn; count++)
  for (int count = 0; count < nbSecond; count++)
  {
    delay(1000);
  }
}

void wateringUnit()
{
  digitalWrite(plantPin, LOW);
  Serial.println("LOW-ON 25s");
  delay1s(timeDelayUnit);
  digitalWrite(plantPin, HIGH);
  Serial.println("HIGH-OFF 25s");
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
  Serial.println("HIGH-OFF 16h");
  digitalWrite(plantPin, HIGH);
  delay1s(timeDelayOff8h);
  delay1s(timeDelayOff8h);
  //   }
}
