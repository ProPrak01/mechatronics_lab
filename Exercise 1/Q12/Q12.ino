#include <LiquidCrystal.h>

LiquidCrystal lcd(2,3,4,8,12,13);
int thres=400;
const int LED_pin = 11;

void setup() {
lcd.begin(16,1);

Serial.begin(9600);
pinMode(3,OUTPUT);
pinMode(LED_pin, OUTPUT );

}

void loop() {

 int val_LDR = analogRead(A3);
  if (val_LDR>thres){
    digitalWrite(LED_pin, HIGH);
    delay(100);
}
else{
digitalWrite(LED_pin, LOW);
    delay(100);
}
    
lcd.print(val_LDR);
Serial.print(val_LDR);
Serial.print("\n");
delay(200);
lcd.clear();
delay(100);

}
