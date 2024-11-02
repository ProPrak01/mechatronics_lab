#include <Servo.h>

Servo myServo;
const int servoPin = 5; 
bool isSweeping = false;
int pos = 0;
int sweepDirection = 1;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(pos);
  printInstructions();
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    
    if (input == '1') {
      isSweeping = true;
      Serial.println("Servo sweeping started.");
    } else if (input == '2') {
      isSweeping = false;
      Serial.println("Servo sweeping stopped.");
    } else if (input != '\n' && input != '\r') { 
      Serial.println("Invalid input. Please try again.");
    }
    
    if (input == '1' || input == '2') {
      printInstructions();
    }
  }
  
  if (isSweeping) {
    pos += sweepDirection;
    
    if (pos <= 0 || pos >= 180) {
      sweepDirection = -sweepDirection;
    }
    
    myServo.write(pos);
    delay(15);  // Adjust this value to change sweep speed
  }
}

void printInstructions() {
  Serial.println("\nEnter a command:");
  Serial.println("1 - Start servo sweeping");
  Serial.println("2 - Stop servo sweeping");
}
