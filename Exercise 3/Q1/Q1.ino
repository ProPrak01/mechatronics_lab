/*
  DigitalReadSerial

  Reads a digital input on pin 2, prints the result to the Serial Monitor

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/DigitalReadSerial
*/

int pushButton = 7;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, OUTPUT);
}

void loop() {
  digitalWrite(pushButton, HIGH);
  Serial.println("em is on!");
  delay(5000);
  digitalWrite(pushButton,LOW);
   Serial.println("em is off!");
  delay(5000);

}
