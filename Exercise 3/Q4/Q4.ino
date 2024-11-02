#include <Servo.h>
#include <LiquidCrystal.h>

Servo servoMotor;

// Define pins for LED colors and LDR
const int redLED = 9;
const int greenLED = 10;
const int blueLED = 11;
const int LDRPin = A2;
int servoPin = 5;

LiquidCrystal lcd(2, 3, 4, 8, 12, 13);

void setup() {
  servoMotor.attach(servoPin);
  lcd.begin(16, 2);
  Serial.begin(9600);
}

void rotateServoToWhitePatch() {
  servoMotor.write(0);
  delay(1000);
}

int readLDR() {
  delay(100);  // Stabilization delay
  int sum = 0;
  // Take average of multiple readings for stability
  for (int i = 0; i < 5; i++) {
    sum += analogRead(LDRPin);
    delay(10);
  }
  return sum / 5;
}

void shineColor(int red, int green, int blue) {
  analogWrite(redLED, red);
  analogWrite(greenLED, green);
  analogWrite(blueLED, blue);
  delay(50);  // Allow LED to stabilize
}

void displayValues(int r, int g, int b) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("R:");
  lcd.print(r);
  lcd.print(" G:");
  lcd.print(g);
  lcd.print(" B:");
  lcd.print(b);

  Serial.print("R: ");
  Serial.print(r);
  Serial.print(" G: ");
  Serial.print(g);
  Serial.print(" B: ");
  Serial.println(b);
}

void AutoCalibrate() {
  // Step 1: Position sensor over white patch
  rotateServoToWhitePatch();
  delay(1000);

  // Step 2: Read initial values at maximum LED intensity
  lcd.clear();
  lcd.print("Initial Reading...");

  // Read Red
  shineColor(255, 0, 0);
  int redValue = readLDR();
  redValue = readLDR();

delay(50);
  // Read Green
  shineColor(0, 255, 0);
  int greenValue = readLDR();
   greenValue = readLDR();
delay(50);
  // Read Blue
  shineColor(0, 0, 255);
  int blueValue = readLDR();
  blueValue = readLDR();
delay(50);
  // Display initial values
  displayValues(redValue, greenValue, blueValue);
  delay(1000);

  // Find the maximum value (minimum intensity)
  int maxValue = max(max(redValue, greenValue), blueValue);

  // Variables to store calibrated intensities
  int redIntensity = 255;
  int greenIntensity = 255;
  int blueIntensity = 255;

  lcd.clear();
  lcd.print("Calibrating...");

  // Adjust intensities using binary search
  for (int i = 0; i < 8; i++) { // 8 iterations for precision
    // Adjust red if needed
    if (redValue != maxValue) {
      redIntensity = findIntensity(redLED, maxValue);
    }

    // Adjust green if needed
    if (greenValue != maxValue) {
      greenIntensity = findIntensity(greenLED, maxValue);
    }

    // Adjust blue if needed
    if (blueValue != maxValue) {
      blueIntensity = findIntensity(blueLED, maxValue);
    }

    // Read final values
    shineColor(redIntensity, 0, 0);
    redValue = readLDR();

    shineColor(0, greenIntensity, 0);
    greenValue = readLDR();

    shineColor(0, 0, blueIntensity);
    blueValue = readLDR();

    displayValues(redValue, greenValue, blueValue);
    delay(500);
  }

  // Display final calibrated values
  lcd.clear();
  lcd.print("Calibrated!");
  lcd.setCursor(0, 1);
  lcd.print("R:");
  lcd.print(redIntensity);
  lcd.print(" G:");
  lcd.print(greenIntensity);
  lcd.print(" B:");
  lcd.print(blueIntensity);

  Serial.println("Calibration Complete!");
  Serial.print("Final LED intensities - R:");
  Serial.print(redIntensity);
  Serial.print(" G:");
  Serial.print(greenIntensity);
  Serial.print(" B:");
  Serial.println(blueIntensity);
   Serial.print("Final ldr - R:");
  Serial.print(redIntensity);
  Serial.print(" G:");
  Serial.print(greenIntensity);
  Serial.print(" B:");
  Serial.println(blueIntensity);
  displayValues(redValue, greenValue, blueValue);
}

// Helper function to find the right intensity using binary search
int findIntensity(int ledPin, int targetValue) {
  int low = 0;
  int high = 255;
  int bestIntensity = 255;
  int bestDiff = 1023;

  while (low <= high) {
    int mid = (low + high) / 2;
    analogWrite(ledPin, mid);
    delay(50);
    int currentValue = readLDR();

    int diff = abs(currentValue - targetValue);
    if (diff < bestDiff) {
      bestDiff = diff;
      bestIntensity = mid;
    }

    if (currentValue < targetValue) {
      high = mid - 1;
    } else if (currentValue > targetValue) {
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return bestIntensity;
}

void loop() {
  AutoCalibrate();
  while (1); // Stop after calibration
}
