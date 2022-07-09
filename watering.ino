int plantPin = 7;
int timeDelayOn = 60 * 10;
int timeDelayOff = 60 * 60 * 3;
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

void loop()
{
  //   int SensorValue = analogRead(A5);
  //   if(SensorValue >= 500)
  //   {
  digitalWrite(plantPin, LOW);
  // Serial.print("LOW-ON ");
  for (int count = 0; count < timeDelayOn; count++)
  {
    delay(1000);
  }
  // delay(timeDelayOn);
  // Serial.print("HIGH-OFF ");
  digitalWrite(plantPin, HIGH);
  for (int count = 0; count < timeDelayOff; count++)
  {
    delay(1000);
  }
  //   }
  //   delay(50);
}
