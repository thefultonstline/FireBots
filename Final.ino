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

int leftDirectionPin = 13;
int rightDirectionPin = 12;
int rightSpeedPin = 3;
int leftSpeedPin = 8;
int fanmotor = 2;

int leftMotorSpeed = 127;
int rightMotorSpeed = 127;

float rightir;
long front;
float rightphototransistor;
float leftphototransistor;

int fronttrigger = 7;
int frontecho = 10;

void setup() {
  // put your setup code here, to run once:

  //set up channel A
  pinMode(rightDirectionPin, OUTPUT);
  pinMode(9, OUTPUT);

  //Set up channel B
  pinMode(leftDirectionPin, OUTPUT);
  pinMode(8, OUTPUT);

  digitalWrite(9,LOW);
  digitalWrite(8,LOW);//disengage brakes

  digitalWrite(rightDirectionPin, LOW);
  digitalWrite(leftDirectionPin, LOW);//set the direction

  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);
  pinMode(fronttrigger, OUTPUT);
  pinMode(frontecho, OUTPUT);
  pinMode(fanmotor, OUTPUT);

  digitalWrite(fanmotor, LOW);//the fan should be off
}

void loop(){
  // put your main code here, to run repeatedly:
  rightphototransistor = (analogRead(A4))*5.0/1023.0;
  leftphototransistor = (analogRead(A5))*5.0/1023.0;
  front = ultrasonic(fronttrigger, frontecho);

  if (leftphototransistor >= 0.5 || rightphototransistor >= 0.5){
    extinguish();
    return;
  }
  
  rightir = (analogRead(A3))/1023.0*5.0;

  if (front > 20){//when not close to wall in the front
    if (rightir < 1.7){
      //Turn right
      leftMotorSpeed = 127;
      rightMotorSpeed = 31;
    }
    else if (rightir > 2.75){
      //lean to the left
      leftMotorSpeed = 95;
      rightMotorSpeed = 127;
    }
    else if (rightir <= 2.75 && rightir > 1.7){
      //go straight
      rightMotorSpeed = 127;
      leftMotorSpeed = 127;
    }
  }
  else if (front <= 20 && front > 7){//when too close to wall when turning
    if (rightir >= 1.7){//turn left when near right wall
      rightMotorSpeed = 127;
      leftMotorSpeed = 0;      
    }
    else if (rightir < 1.7){
      rightMotorSpeed = 0;
      leftMotorSpeed = 127;
    }
  }
  else if (front <= 7){
    backUpAndTurnLeft();
  }
  analogWrite(rightSpeedPin, rightMotorSpeed);
  analogWrite(leftSpeedPin, leftMotorSpeed);
}

void backUpAndTurnLeft(){
//run motors backward
  digitalWrite(rightDirectionPin, HIGH);
  digitalWrite(leftDirectionPin, HIGH);
  rightMotorSpeed = 127;
  leftMotorSpeed = 127;
  analogWrite(rightSpeedPin, rightMotorSpeed);
  analogWrite(leftSpeedPin, leftMotorSpeed);
  delay(500);
  digitalWrite(rightDirectionPin, LOW);
  digitalWrite(leftDirectionPin, LOW);
//turnleft
  rightMotorSpeed = 127;
  leftMotorSpeed = 0;
  analogWrite(rightSpeedPin, rightMotorSpeed);
  analogWrite(leftSpeedPin, leftMotorSpeed);
  delay(1000);
}

long ultrasonic(int trigPin, int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  return duration/58;
}

void extinguish(){
  if (leftphototransistor > rightphototransistor){
    rightMotorSpeed = 95;
    leftMotorSpeed = 0;
  }
  else if (leftphototransistor < rightphototransistor){
    rightMotorSpeed = 0;
    leftMotorSpeed = 95;
  }
  analogWrite(rightSpeedPin, rightMotorSpeed);
  analogWrite(leftSpeedPin, leftMotorSpeed);

  if (leftphototransistor >= 1.00 && rightphototransistor >= 1.00 && front <= 5){
    digitalWrite(fanmotor, HIGH);//turn on the fan
    digitalWrite(9,HIGH);//
    digitalWrite(8,HIGH);
  }
}
