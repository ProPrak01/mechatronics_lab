const int buttonPin = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
  
   int digitalVal = digitalRead(buttonPin); // Take a reading

  if(HIGH == digitalVal)
  {
    digitalWrite(13,LOW); 
  }
  else
  {
    digitalWrite(13,HIGH);
  }
}
