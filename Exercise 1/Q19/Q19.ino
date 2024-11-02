#include <LiquidCrystal.h>

// Initialize the LCD library with the numbers of the interface pins
LiquidCrystal lcd(2,3,4,8,12,13);

const int STRING_LENGTH = 8;  // 7 numbers + 1 character
char receivedString[STRING_LENGTH + 1];  // +1 for null terminator
int extractedNumbers[7];

void setup() {
  Serial.begin(9600);  // Initialize serial communication at 9600 bps
  lcd.begin(16, 2);    // Set up the LCD's number of columns and rows
  lcd.print("Waiting for data...");
}

void loop() {
  if (Serial.available() >= STRING_LENGTH) {
    // Read the incoming string
    Serial.readBytes(receivedString, STRING_LENGTH);
    receivedString[STRING_LENGTH] = '\0';  // Null-terminate the string
    
    // Check if the string is in the correct format
    if (receivedString[7] == 'c') {
      // Extract numbers from the string
      for (int i = 0; i < 7; i++) {
        extractedNumbers[i] = receivedString[i] - '0';
      }
      
      // Display the numbers on LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Nums: ");
      for (int i = 0; i < 7; i++) {
        lcd.print(extractedNumbers[i]);
        if (i < 6) lcd.print(",");
      }
      
      // Display some of the numbers on the second line (adjust as needed)
      lcd.setCursor(0, 1);
      lcd.print("1st: ");
      lcd.print(extractedNumbers[0]);
      lcd.print(" Last: ");
      lcd.print(extractedNumbers[6]);
    } else {
      lcd.clear();
      lcd.print("Invalid format");
    }
    
    // Clear the serial buffer
    while (Serial.available() > 0) {
      Serial.read();
    }
  }
}
