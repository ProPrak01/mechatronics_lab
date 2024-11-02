const int proximity_Pin=A0;
void setup()
{
pinMode(proximity_Pin, INPUT);
Serial.begin(9600);
}
void loop()
{
int sensorValue = analogRead(proximity_Pin);

//delay(500);
Serial.println(sensorValue);
delay(100);


}
