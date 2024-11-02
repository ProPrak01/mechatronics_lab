#include <LiquidCrystal.h>
const int LDR = "A3";
int val_LDR = 0;
LiquidCrystal lcd(2,3,4,8,12,13);

void setup() {
lcd.begin(16,1);

Serial.begin(9600);

}

void loop() {
 val_LDR = analogRead(LDR);

lcd.print(val_LDR);
Serial.print(val_LDR);
Serial.print("\n");
 delay(200);
  lcd.clear();
   delay(100);
}
