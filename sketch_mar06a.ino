/*
 * 
Function          Channel A   Channel B
Direction         Digital 12  Digital 13
Speed (PWM)       Digital 3   Digital 11
Brake             Digital 9    Digital 8
Current Sensing     Analog 0  Analog 1
 */

//LEFT = B
//RIGHT = A


float right;
float rightwallvalue = 2.5;
float rightturnvalue = 1.0;

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

  digitalWrite(12,1);
  digitalWrite(13,0);//direction

  pinMode(A4, INPUT);//ir


  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
right = (analogRead(A4))*5.0/1024.0;
  
  
  if (right < rightwallvalue){
    //Turn Right
    digitalWrite(5, LOW);
    analogWrite(11, 127);//left motor
    analogWrite(3, 63);//right motor
  }
  if (right >= rightwallvalue){
    //GO Straight
    digitalWrite(5, HIGH);
    analogWrite(11, leftMotorForward);//left motor
    analogWrite(3, rightMotorForward);//right motor
  }
  

}
