int led2 = 11;
int led1 = 12;
int led0 = 13;

void setup() {
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  reset();
  for(int i = 0; i < 8; ++i) 
  {
    signal( led2, ((i >> 2) % 2) == 1); // See what I did there? Ninja bit magic! 
    signal( led1, ((i >> 1) % 2) == 1); // Got the idea from 
    signal( led0, ((i >> 0) % 2) == 1); // http://forums.adafruit.com/viewtopic.php?f=20&t=12289
    delay(2000);
  }
}

// Set all LEDs off to make sure we start at zero
void reset() {
  signal( led2, 0);
  signal( led1, 0);
  signal( led0, 0);
}

void signal(int led, bool on) {
  if(on) {
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);
  }
}