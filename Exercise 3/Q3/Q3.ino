#include <Servo.h>
#include <LiquidCrystal.h>
Servo servoMotor;

// Define the pins for the LED colors and LDR
const int redLED = 9;
const int greenLED = 10;
const int blueLED = 11;
const int LDRPin = A2;  // LDR connected to an analog pin

int servoPin = 5;  // Servo motor connected to pin 6

LiquidCrystal lcd(2,3,4,8,12,13); // Initialize LCD with appropriate pins

void setup() {
  servoMotor.attach(servoPin);  // Attach the servo motor
  lcd.begin(16, 2);  // Set up LCD with 16 columns and 2 rows
  Serial.begin(9600);  // Start serial communication for debugging
}

void rotateServoToWhitePatch() {
  servoMotor.write(0);
  delay(1000);
}

int readLDR() {
  delay(100);  
  return analogRead(LDRPin);  
}

void shineColor(int red, int green, int blue) {
  analogWrite(redLED, red);
  analogWrite(greenLED, green);
  analogWrite(blueLED, blue);
}

void ManualCalibrate() {
  rotateServoToWhitePatch(); 
  delay(1000);

  while (true) {
      // Step 1: Shine red, green, and blue colors individually
    int redValue, greenValue, blueValue;
  
    // Shine red
    shineColor(255, 0, 0); 
    delay(100);
    redValue = readLDR();  
    redValue = readLDR(); 
 delay(100);

    // Shine green
    shineColor(0, 255, 0); 
    delay(100);
    greenValue = readLDR();  
    greenValue = readLDR();
  delay(100);

    // Shine blue
    shineColor(0, 0, 255); 
    delay(100);
    blueValue = readLDR();  
    blueValue = readLDR();
 delay(100);
    // Step 2: Print the read values to the LCD
    lcd.clear();
    lcd.print(" R"); lcd.print(redValue);
    lcd.print(" G"); lcd.print(greenValue);
    lcd.print(" B"); lcd.print(blueValue);

    // Step 3: Print values to serial for debugging
    Serial.print("R: "); Serial.print(redValue);
    Serial.print(" G: "); Serial.print(greenValue);
    Serial.print(" B: "); Serial.println(blueValue);
    //Serial.print(" ldr: "); Serial.println( readLDR());
    // Step 4: Wait for stop command (enter '1' in the serial monitor)
    if (Serial.available() > 0) {
      char command = Serial.read();
      if (command == '1') {
        lcd.clear();
        lcd.print("Calibration Done");
        break;  
      }
    }
    
    delay(500); 
  }
}

void loop() {
  // Start manual calibration
  ManualCalibrate();
      
}
