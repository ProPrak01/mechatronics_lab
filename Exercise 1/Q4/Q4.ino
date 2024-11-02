const int buttonPin1 = 7;
const int buttonPin2 = 8;
const int buttonPin3 = 9;
const int led1 = 11;
const int led2 = 12;
const int led3 = 13;
void setup() {
  
  pinMode(buttonPin1, INPUT_PULLUP);
    pinMode(buttonPin2, INPUT_PULLUP);

  pinMode(buttonPin3, INPUT_PULLUP);

  pinMode(led1, OUTPUT);
   pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
}

void loop() {
  
   int digitalVal1 = digitalRead(buttonPin1); 
  int digitalVal2 = digitalRead(buttonPin2); 
  int digitalVal3 = digitalRead(buttonPin3); 
  if(HIGH == digitalVal1)
  {
    digitalWrite(led1,LOW); 
  }
  else{
    digitalWrite(led1,HIGH);
  }
   if(HIGH == digitalVal2)
  {
    digitalWrite(led2,LOW); 
  }
   else{
    digitalWrite(led2,HIGH);
  }
   if(HIGH == digitalVal3)
  {
    digitalWrite(led3,LOW); 
  }
   else{
    digitalWrite(led3,HIGH);
  }

}
