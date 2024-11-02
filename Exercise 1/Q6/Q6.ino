const int G = 3;
const int B = 5;
const int R = 6;
void setup() {
  // put your setup code here, to run once:
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void loop() {
 for(int i =0; i < 255; i++){
  analogWrite(R, i);
  delay(10);
 }
delay(1000);

 for(int i =0; i < 255; i++){
  analogWrite(G, i);
  delay(10);
 }
delay(1000);

 for(int i =0; i < 255; i++){
  analogWrite(B, i);
  delay(10);
 }
delay(1000);

}
