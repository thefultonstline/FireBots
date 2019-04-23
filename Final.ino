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

float rightir;
int front;
float rightphototransistor;
float leftphototransistor;

int fronttrigger = 7;
int frontecho = 10;
int fanmotor = 2;

int leftdirection = 13;
int rightdirection = 12;
int leftspeed = 11;
int rightspeed = 3;
int leftbrake = 8;
int rightbrake = 9;



void setup() {
  pinMode(rightdirection, OUTPUT); //Initiates Motor Channel A direction pin
  pinMode(rightbrake, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B-left
  pinMode(leftdirection, OUTPUT); //Initiates Motor Channel B direction pin
  pinMode(leftbrake, OUTPUT);  //Initiates Brake Channel B pin


  digitalWrite(rightbrake,LOW);
  digitalWrite(leftbrake,LOW);//disengage brakes

  digitalWrite(rightdirection,LOW);
  digitalWrite(leftdirection,HIGH);//direction

  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A5, INPUT);


  pinMode(frontecho, INPUT);
  pinMode(fronttrigger, OUTPUT);
  pinMode(fanmotor, OUTPUT);

}

void loop() {
  rightir = (analogRead(A3))*5.0/1024.0;
  front = ultrasonic(fronttrigger, frontecho);
  rightphototransistor = (analogRead(A4))*5.0/1024.0;
  leftphototransistor = (analogRead(A5))*5.0/1024.0;

  delay(100);//delay for registers to update
  
  if (leftphototransistor >= 2.00 || rightphototransistor >= 2.00){
    extinguish();
    return;//ends the loop cycle early-> goes back to beginning
  }


  if(front > 20){
    if (rightir < 1.7){
    //Turn Right
      analogWrite(leftspeed, 127);//left motor
      analogWrite(rightspeed, 31);//right motor
    }
    else if (rightir > 2.75){
      analogWrite(leftspeed, 95);//left motor
      analogWrite(rightspeed, 127);//right motor

    }
     else if (rightir <= 2.75 && rightir > 1.7){//straight
      analogWrite(leftspeed, 127);//left motor
      analogWrite(rightspeed, 127);//right motor  
    }
    
  }

  if (front <= 20 && front > 7){//
    if (rightir >= 1.7){//right is near
      analogWrite(rightspeed, 127);
      analogWrite(11, 0);//turning left
    }
    else if (rightir < 1.7){//right is far, sw room
      analogWrite(rightspeed, 0);
      analogWrite(11, 127);//turning right?
    }
  }
  if (front <= 7){//backup and turn left
    backupAndTurnLeft(); 
  }

}

void backupAndTurnLeft(){

//run motors backward
  digitalWrite(rightdirection,HIGH);
  digitalWrite(leftdirection,LOW);
  analogWrite(rightspeed, 95);
  analogWrite(leftspeed, 95);
  delay(750);
  digitalWrite(rightdirection,LOW);
  digitalWrite(leftdirection,HIGH);
//turnleft
  analogWrite(rightspeed, 127);
  analogWrite(leftspeed, 0);
  delay(1000);
}

int ultrasonic(int trigPin, int echoPin){
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
    analogWrite(rightspeed, 63);//turn left
    analogWrite(leftspeed, 0);
  }
  else if (rightphototransistor < leftphototransistor){//turning right
    if (rightir > 2.75){//if close to wall go straight instead
      analogWrite(rightspeed, 63);
      analogWrite(leftspeed, 63);
    }
    else{//turn to right
      analogWrite(rightspeed, 0);
      analogWrite(leftspeed, 63);
    }
  }

  if (leftphototransistor >= 4.00 || rightphototransistor >= 4.00){
      digitalWrite(fanmotor, HIGH);//turn on fan
      digitalWrite(rightbrake, HIGH);//stop robot
      digitalWrite(leftbrake, HIGH);
    }
}
