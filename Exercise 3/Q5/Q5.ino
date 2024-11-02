#include <Servo.h>
#include <LiquidCrystal.h>

Servo servoMotor;
const int redLED = 9;
const int greenLED = 10;
const int blueLED = 11;
const int LDRPin = A2;
int servoPin = 5;
LiquidCrystal lcd(2, 3, 4, 8, 12, 13);
int global_cal_int ;
// Function to shine specified color
void shineColor(int redIntensity, int greenIntensity, int blueIntensity) {
  analogWrite(redLED, redIntensity);
  analogWrite(greenLED, greenIntensity);
  analogWrite(blueLED, blueIntensity);
}

// Function to read LDR value
int readLDR() {
  return analogRead(LDRPin);
}

// Function to rotate servo to white patch for calibration
void rotateServoToWhitePatch() {
 
  servoMotor.write(0);  // Adjust this angle based on white patch location
  delay(500);
  servoMotor.detach();
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
        global_cal_int = blueValue;
         lcd.clear();
         delay(50);
        lcd.print("global value:");
         lcd.setCursor(0, 1);
         lcd.print(global_cal_int);
          delay(200);
        break;  
      }
    }
    
    delay(500); 
  }
}
// Auto Calibration Function
void AutoCalibrate() {
  rotateServoToWhitePatch();
  delay(500);

  int redValue, greenValue, blueValue;

  // Shine red, green, and blue light individually and read LDR values
  shineColor(255, 0, 0);
  delay(50);
  redValue = readLDR();

  shineColor(0, 255, 0);
  delay(50);
  greenValue = readLDR();

  shineColor(0, 0, 255);
  delay(50);
  blueValue = readLDR();
  shineColor(0, 0, 0);
  // Find the max value (minimum intensity)
  int maxValue = max(redValue, max(greenValue, blueValue));

  // Adjust intensities of other colors to equalize with max value
  for (int i = 0; i <= 255; i++) {
    if (redValue < maxValue) {
      shineColor(i, 0, 0);
      delay(50);
      redValue = readLDR();
    }
    if (greenValue < maxValue) {
      shineColor(0, i, 0);
      delay(50);
      greenValue = readLDR();
    }
    if (blueValue < maxValue) {
      shineColor(0, 0, i);
      delay(50);
      blueValue = readLDR();
    }
    if (redValue == maxValue && greenValue == maxValue && blueValue == maxValue) {
     global_cal_int = maxValue;
     lcd.print(global_cal_int);
      break;
    }
  }

  lcd.clear();
  lcd.print("Auto Calibrated");
  delay(2000);
}

// Function to display color values at each servo position
void SweepAndDisplayColor() {
  servoMotor.attach(servoPin);
  for (int pos = 0; pos <= 180; pos += 10) {
    servoMotor.write(pos);
    delay(500);

    // Read RGB values
    shineColor(255, 0, 0); delay(50);
    int redValue = readLDR();

    shineColor(0, 255, 0); delay(50);
    int greenValue = readLDR();

    shineColor(0, 0, 255); delay(50);
    int blueValue = readLDR();
    //shineColor(0, 0, 0);
    // Display values
    lcd.clear();
    lcd.setCursor(0, 0);
//    lcd.print("Pos: "); lcd.print(pos);
    if((abs(redValue- blueValue)<10 && abs(greenValue- blueValue)<10 && abs(greenValue- redValue)<10 )){
        lcd.clear();
        lcd.print("White Color");
        lcd.print(global_cal_int);
    }
    else if(redValue == min(redValue , min(blueValue , greenValue))){
        lcd.clear();
      lcd.print("Red Color");
      
    }
    else if(blueValue == min(redValue , min(blueValue , greenValue))){
         lcd.clear();
       lcd.print("Blue Color");
    }
    else if(greenValue == min(redValue , min(blueValue , greenValue))){
        lcd.clear();
      lcd.print("Green Color");
    }
    
    
    
    lcd.setCursor(0, 1);
    lcd.print("R:"); lcd.print(redValue);
    lcd.print(" G:"); lcd.print(greenValue);
    lcd.print(" B:"); lcd.print(blueValue);

    delay(1000);
  }
  servoMotor.detach();
}

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
   servoMotor.attach(servoPin);
  servoMotor.write(0);
  delay(500);
  lcd.print("Select Calibration");
  lcd.setCursor(0, 1);
  lcd.print("1: Manual 2: Auto");
 
  while (true) {
    if (Serial.available() > 0) {
      char choice = Serial.read();
      if (choice == '1') {
        lcd.clear();
        lcd.print("Manual Calibration");
        delay(1000);
          lcd.clear();
        ManualCalibrate();
        break;
      } else if (choice == '2') {
        lcd.clear();
        lcd.print("Auto Calibration");
         delay(1000);
         lcd.clear();
        AutoCalibrate();
        break;
      }
    }
  }

  lcd.clear();
  lcd.print("Sweep & Display");
  SweepAndDisplayColor();
}

void loop() {
  // Main loop can remain empty as everything is handled in setup for this task.
}
