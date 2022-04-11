void setup()
{
  Serial.begin(9600);
}

void loop()
{
  int moist = analogRead(A5);
  Serial.println(moist);
}