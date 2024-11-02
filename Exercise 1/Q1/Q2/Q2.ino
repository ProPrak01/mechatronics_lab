
void setup() {
  pinMode(11, OUTPUT);
 pinMode(12, OUTPUT);
 pinMode(13, OUTPUT);
}

void loop() {
    digitalWrite(11, 1);
delay(100);
    digitalWrite(11, 0);
    delay(100);
     digitalWrite(12, 1);
delay(100);
    digitalWrite(12, 0);
    delay(100);
        digitalWrite(13, 1);
delay(100);
    digitalWrite(13, 0);
    delay(100);
}
