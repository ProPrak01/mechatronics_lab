#include <Servo.h>

Servo myServo;
const int servoPin = 5  ;  
bool isSweeping = false;
int pos = 0;
int sweepDirection = 1;
const int proximity_Pin=A0;

void setup() {
  pinMode(proximity_Pin, INPUT);
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(pos);
}

void loop() {
  int sensorValue = analogRead(proximity_Pin);
    Serial.println("SENSOR VALUE : ");
    Serial.println(sensorValue);
    if (sensorValue > 400) {
      isSweeping = true;
      Serial.println("Servo sweeping started.");
    } else {
      isSweeping = false;
      Serial.println("Servo sweeping stopped.");
    }
  
  if (isSweeping) {
    pos += sweepDirection;
    
    if (pos <= 0 || pos >= 180) {
      sweepDirection = -sweepDirection;
    }
    
    myServo.write(pos);
    delay(15);  
  }
}
