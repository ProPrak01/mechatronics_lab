const int pin_a2 = "A1";
int poten_value = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  poten_value = analogRead(pin_a2);
  Serial.println(poten_value);
  delay(100);
}
