#include <LiquidCrystal.h>

//rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7
LiquidCrystal lcd(2,3,4,8,12,13);

void setup() {
//lcd.begin(16,1);
  lcd.begin(16,2);
  lcd.print("hello, world!");

}

void loop() {
 
}
