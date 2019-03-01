float right;
float rightvalue = 0.85;

void setup() {
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B-left
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin


  digitalWrite(9,LOW);
  digitalWrite(8,LOW);//disengage brakes

  digitalWrite(12,0);
  digitalWrite(13,1);//direction

  pinMode(A4, INPUT);//ir

}

void loop() {
  // put your main code here, to run repeatedly:


  right = (analogRead(A4))*5/1024;


  if (right > rightvalue){
    analogWrite(11, 127);
    analogWrite(3, 63);
  }
  else{
  analogWrite(11, 127);
  analogWrite(3, 95);
  }

}
