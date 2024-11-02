#include <Servo.h>
// const int pin_a2 = "A1";
// int poten_value = 0;
int pos = 0; 

Servo myservo;  

void setup() {
  // put your setup code here, to run once:
 myservo.attach(5);
  myservo.write(0)  ;
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
// poten_value = analogRead(pin_a2);
int poten_value = analogRead(A1);
  Serial.print(poten_value);
   Serial.print("\n");

 int mapped_value = map(poten_value, 0, 1023, 0, 180);

  myservo.write(mapped_value); 
  delay(10);
}
