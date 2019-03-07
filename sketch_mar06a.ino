float right;
float rightwallvalue = 2.5;
float rightturnvalue = 1.2;

float leftMotorForward = 127;
float rightMotorForward = 127;
float motorStop = 0;

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

  pinMode(5, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
right = (analogRead(A4))*5.0/1024.0;
  
  
  if (right < rightwallvalue){
    //Turn Right
    digitalWrite(5, HIGH);
    analogWrite(11, 127);//left motor
    analogWrite(3, 63);//right motor
  }
  if (right >= rightwallvalue){
    //GO Straight
     digitalWrite(5, LOW);
  analogWrite(11, 123);//left motor
  analogWrite(3, 127);//right motor
  
  }
  

}
