#include <LiquidCrystal.h>
int IRSensor = A0; // connect IR sensor module to Arduino pin D9
int LED = 13; // connect LED to Arduino pin 13
int electro = 7;

LiquidCrystal lcd(2, 3, 4, 8, 12, 13);
void setup(){
  Serial.begin(9600); 
  Serial.println("Serial Working"); // Test to check if serial is working or not
  pinMode(IRSensor, INPUT); // IR Sensor pin INPUT
  pinMode(LED, OUTPUT); // LED Pin Output
  pinMode(electro,OUTPUT);
}


void loop(){
  int sensorStatus = analogRead(IRSensor); 
  //Serial.println(sensorStatus);
  if (sensorStatus > 300) 
  {
    // if the pin is high turn off the onboard Led
    digitalWrite(LED, LOW); // LED LOW
    Serial.println("Object NOT Detected! em is off !!"); 
    digitalWrite(electro,LOW);
    lcd.clear();
    lcd.print("Object Not Detect");
    
    }
  else  {
    //else turn on the onboard LED
    digitalWrite(LED, HIGH); // LED High
    Serial.println("Object Detected! em is on !!");
    digitalWrite(electro,HIGH);
     lcd.clear();
    lcd.print("Object detected");
    
  }
  delay(10);
}
