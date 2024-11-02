#include <Servo.h>

Servo myservo;
int servoPos = 90;  
const int clockwiseSwitch = 7;
const int counterClockwiseSwitch = 8;
int lastClockwiseState = HIGH;
int lastCounterClockwiseState = HIGH;

void setup() {
  myservo.attach(5);
  myservo.write(servoPos);
  pinMode(clockwiseSwitch, INPUT_PULLUP);
  pinMode(counterClockwiseSwitch, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  int clockwiseState = digitalRead(clockwiseSwitch);
  int counterClockwiseState = digitalRead(counterClockwiseSwitch);

 
  if (clockwiseState == LOW && lastClockwiseState == HIGH) {
    if (servoPos < 180) {
      servoPos++;
      myservo.write(servoPos);
      Serial.print("Clockwise - Position: ");
      Serial.println(servoPos);
    }
  }

  
  if (counterClockwiseState == LOW && lastCounterClockwiseState == HIGH) {
    if (servoPos > 0) {
      servoPos--;
      myservo.write(servoPos);
      Serial.print("Counter-clockwise - Position: ");
      Serial.println(servoPos);
    }
  }

  lastClockwiseState = clockwiseState;
  lastCounterClockwiseState = counterClockwiseState;

  delay(50);  
}
