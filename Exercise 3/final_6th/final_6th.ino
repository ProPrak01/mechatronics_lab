#include <Servo.h>
#include <LiquidCrystal.h>

Servo servoMotor;
Servo servoMotor2;
const int redLED = 9;
const int greenLED = 10;
const int blueLED = 11;
const int LDRPin = A2;
const int IRSensor = A0;
const int electro = 7;
int servoPin = 5;
int servoPin2 = 6;

String initial_pos = "red";
String final_pos = "blue";
LiquidCrystal lcd(2, 3, 4, 8, 12, 13);
int global_cal_int;
// Function to shine specified color
void shineColor(int redIntensity, int greenIntensity, int blueIntensity)
{
  analogWrite(redLED, redIntensity);
  analogWrite(greenLED, greenIntensity);
  analogWrite(blueLED, blueIntensity);
}

// Function to read LDR value
int readLDR()
{
  analogRead(LDRPin);
  return analogRead(LDRPin);
}

// Function to rotate servo to white patch for calibration
void rotateServoToWhitePatch()
{

  servoMotor.write(0); // Adjust this angle based on white patch location
  delay(500);
  servoMotor.detach();
}


void ManualCalibrate()
{
  rotateServoToWhitePatch();
  delay(1000);

  while (true)
  {
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
    lcd.print(" R");
    lcd.print(redValue);
    lcd.print(" G");
    lcd.print(greenValue);
    lcd.print(" B");
    lcd.print(blueValue);

    // Step 3: Print values to serial for debugging
    Serial.print("R: ");
    Serial.print(redValue);
    Serial.print(" G: ");
    Serial.print(greenValue);
    Serial.print(" B: ");
    Serial.println(blueValue);

    // Serial.print(" ldr: "); Serial.println( readLDR());
    //  Step 4: Wait for stop command (enter '1' in the serial monitor)
    if (Serial.available() > 0)
    {
      char command = Serial.read();
      if (command == '1')
      {
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
    global_cal_int = blueValue;
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

void sweepMotor2(int condition)
{
  int flag = 0;
  while (flag == 0)
  {
     servoMotor2.attach(servoPin2);
    for (int pos = 180; pos >= 90; pos -= 10)
    {
      servoMotor2.write(pos);
      if (analogRead(IRSensor) < 300)
      {
        Serial.println("Object Detected");
        flag = 1;
        if (condition == 1)
        {
          digitalWrite(electro, HIGH);
          Serial.println("Object Held");
          lcd.clear();
          lcd.print("Object Held");
          delay(100);
        }
        else
        {
          digitalWrite(electro, LOW);
          Serial.println("Object Removed");
          
        }

        delay(2000);
        break;
      }
      delay(50);
    }
    lcd.clear();
    lcd.print("check1");
     for (int pos = servoMotor2.read(); pos <= 180; pos += 10){
       servoMotor2.write(pos);
       delay(50);
      }
      servoMotor2.detach();
   lcd.clear();
    lcd.print("check2");
    
   delay(1000);
  }
 // delay(2000);



 
  //servoMotor2.write(180);
//  delay(1000);
}

void DetectColor()
{
  SweepAndDisplayColor(initial_pos);
  sweepMotor2(1);
  Serial.println("going to final destination");
  
  //delay(2000);
    Serial.println("going to final destination 1");

//  servoMotor.attach(servoPin);
//  Serial.println("going to final destination 2");
//
//   
//  
//  servoMotor.write(0);
//    Serial.println("going to final destination 3");
 lcd.clear();
 lcd.print("check3->");
// servoMotor.attach(servoPin);
// lcd.print(servoMotor.read());
  delay(100);
 lcd.clear();
 lcd.print("check4");
 servoMotor.attach(servoPin);
for(int  k = servoMotor.read() ; k >=0 ; k-=3){
  servoMotor.write(k);
  Serial.print("this:");
    Serial.print(k);
   Serial.println();
  delay(100);
}
servoMotor.detach();
lcd.clear();
lcd.print("check5");

Serial.println("going to final destination 2");
  delay(3000);
    Serial.println("going to final destination 4");

   servoMotor.detach();
 // Serial.println("going to final destination 5");

  
  Serial.println("starting to go to final des");
  SweepAndDisplayColor(final_pos);
  sweepMotor2(0);
}

// Function to display color values at each servo position
void SweepAndDisplayColor(String curr_color)
{
  servoMotor.attach(servoPin);
  for (int pos = 0; pos <= 180; pos += 10)
  {

    servoMotor.write(pos);
    delay(500);

    // Read RGB values
    shineColor(255, 0, 0);
    delay(50);
    int redValue = readLDR();

    shineColor(0, 255, 0);
    delay(50);
    int greenValue = readLDR();

    shineColor(0, 0, 255);
    delay(50);
    int blueValue = readLDR();
    shineColor(0, 0, 0);
    // Display values
    lcd.clear();
    lcd.setCursor(0, 0);
    //    lcd.print("Pos: "); lcd.print(pos);
    if ((abs(redValue - blueValue) < 6 && abs(greenValue - blueValue) < 6 && abs(greenValue - redValue) < 6))
    {
      lcd.clear();
      lcd.print("White Color");
    }
    else if (redValue == min(redValue, min(blueValue, greenValue)))
    {
      lcd.clear();
      lcd.print("Red Color");
      if (curr_color == "red")
      {
        break;
      }
    }
    else if (blueValue == min(redValue, min(blueValue, greenValue)))
    {
      lcd.clear();

      lcd.print("Blue Color");
      if (curr_color == "blue")
      {
        break;
      }
    }
    else if (greenValue == min(redValue, min(blueValue, greenValue)))
    {
      lcd.clear();
      lcd.print("Green Color");
      if (curr_color == "green")
      {
        break;
      }
    }

    lcd.setCursor(0, 1);
    lcd.print("R");
    lcd.print(redValue);
    lcd.print("G:");
    lcd.print(greenValue);
    lcd.print("B:");
    lcd.print(blueValue);

    delay(1000);
  }
  servoMotor.detach();
}

void setup()
{
  pinMode(IRSensor, INPUT); // IR Sensor pin INPUT
  pinMode(electro, OUTPUT);
}

void loop()
{
  // Main loop can remain empty as everything is handled in setup for this task.

  Serial.begin(9600);
  lcd.begin(16, 2);
  servoMotor.attach(servoPin);
  servoMotor2.attach(servoPin2);
  servoMotor2.write(180);
  servoMotor.write(0);
  delay(500);
  lcd.print("Select Calibration");
  lcd.setCursor(0, 1);
  lcd.print("1: Manual 2: Auto");


 // lcd.clear();
//  while (true)
//  {
//    if (Serial.available() > 0)
//    {
//      char choice = Serial.read();
//      if (choice == '1')
//      {
//        lcd.clear();
//        lcd.print("Manual Calibration");
//        delay(1000);
//        lcd.clear();
//        ManualCalibrate();
//        break;
//      }
//      else if (choice == '2')
//      {
//        lcd.clear();
//        lcd.print("Auto Calibration");
//        delay(1000);
//        lcd.clear();
//        AutoCalibrate();
//        break;
//      }
//    }
//  }
lcd.clear();
        lcd.print("Auto Calibration");
        delay(1000);
        lcd.clear();
        AutoCalibrate();
  lcd.print("Sweep & Display");
  // SweepAndDisplayColor();
  DetectColor();
//  while(true){}
}
