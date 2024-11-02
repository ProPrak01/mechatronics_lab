const int pin_a2 = "A1";
int poten_value = 0;
const int R = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
   pinMode(R, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  poten_value = analogRead(pin_a2);
  int ledBrightness = map(poten_value, 0, 1023, 0, 255);
  analogWrite(R, ledBrightness);
  Serial.println(poten_value);
  delay(100);
}

