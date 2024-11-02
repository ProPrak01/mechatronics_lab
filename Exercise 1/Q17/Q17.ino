#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,8,12,13);
const int buttonPin = 9;
int buttonState = 0; 
int counter = 0;
int n= 0 ;
void setup() {
  // put your setup code here, to run once:
lcd.begin(16,1);
Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop() {
   buttonState = digitalRead(buttonPin);
  // put your main code here, to run repeatedly:
   if (buttonState == HIGH) {
   n = 1;
  }  
  if( n == 1 && buttonState == LOW){
    n = 0;
    counter++;
  }


lcd.print(counter);
lcd.print("\n");
Serial.print(counter);
Serial.print("\n");


}
