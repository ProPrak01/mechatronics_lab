const int proximity_Pin=5;
const int led_pin = 11;

void setup()
{
pinMode(proximity_Pin, INPUT);
pinMode(led_pin, OUTPUT);
Serial.begin(9600);
}
void loop()
{
int sensorValue = digitalRead(proximity_Pin);
if(sensorValue==HIGH)
{
Serial.println("no Object");

digitalWrite(led_pin,LOW);
delay(500);
}
else
{
Serial.println("Object Detected");
digitalWrite(led_pin,HIGH);
delay(500);
}
}
