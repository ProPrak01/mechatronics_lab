#include <Servo.h>

Servo myservo;  

int pos = 0;    

void setup() {
  myservo.attach(5);
  myservo.write(0)  ;
Serial.begin(9600);
}

void loop() {



  for (pos = 0; pos <= 180; pos += 1) { 
   
    myservo.write(pos); 
    //Serial.print(pos);             
   //Serial.print("\n");
    delay(2);                       
  }
    Serial.print(myservo.read());
  Serial.print("\n");
  for (pos = 180; pos >= 0; pos -= 1) { 
    myservo.write(pos); 
    // Serial.print(pos);             
    //Serial.print("\n");
    delay(2);                      
  }
      Serial.print(myservo.read());
  Serial.print("\n");
}