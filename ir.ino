  float x;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  x = analogRead(A4)*5.0/1024.0;
  Serial.println(x);
  delay(50);}
