#include <LiquidCrystal.h>

// Initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(2,3,4,8,12,13);

const int ldrPin = A3;  // LDR connected to analog pin A0
const int threshold = 700;  // Adjust this value based on your LDR and lighting conditions
const long duration = 5000;  // 5 seconds in milliseconds

int count = 0;
bool fingerDetected = false;
unsigned long startTime;

void setup() {
  lcd.begin(16, 2);  // Set up the LCD's number of columns and rows
  lcd.print("Finger Count: 0");
  startTime = millis();
  Serial.begin(9600);
}

void loop() {
  
  int ldrValue = analogRead(ldrPin);
   Serial.print(ldrValue);
   Serial.print("\n");
   Serial.print("count :");
    Serial.print(count);
    Serial.print("\n");
  if (ldrValue < threshold && !fingerDetected) {
    fingerDetected = true;
    count++;
    lcd.setCursor(14, 0);
    lcd.print(count);
   
  } else if (ldrValue >= threshold) {
    fingerDetected = false;
  }

  if (millis() - startTime >= duration) {
    lcd.clear();
    lcd.print("Time's up!");
    lcd.setCursor(0, 1);
    lcd.print("Final count: ");
    lcd.print(count);
    while(1);  // Stop the program
  }
}
