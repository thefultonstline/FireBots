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
float rightwallvalue = 1.7;
float front;

int fronttrigger = 7;
int frontecho = 10;

float leftMotorForward = 127;
float rightMotorForward = 127;

void setup() {
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B-left
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin


  digitalWrite(9,LOW);
  digitalWrite(8,LOW);//disengage brakes

  digitalWrite(12,0);
  digitalWrite(13,0);//direction

  pinMode(A4, INPUT);//ir

  pinMode(10, INPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  right = (analogRead(A4))*5.0/1024.0;
  front = ultrasonic(fronttrigger, frontecho);
    Serial.print("Righton  ");

  Serial.print(right);
    Serial.print(",  froant  ");

    Serial.println(front);


  if(front > 20){
    if (right < rightwallvalue){
    //Turn Right
    analogWrite(11, 127);//left motor
    analogWrite(3, 31);//right motor
    Serial.println("turn right");
    }
    else if (right > 2.75){
      analogWrite(11, 95);//left motor
      analogWrite(3, 127);//right motor
          Serial.println("leanleft");

    }
     else if (right <= 2.75 && right > rightwallvalue){//straight
      analogWrite(11, 127);//left motor
      analogWrite(3, 127);//right motor  
                Serial.println("striaght");

    }
    
  }

  if (front <= 20 && front > 7){//
    if (right >= rightwallvalue){//right is near
      analogWrite(3, 127);
      analogWrite(11, 0);//turning left
    }
    else if (right < rightwallvalue){//right is far, sw room
      analogWrite(3, 0);
      analogWrite(11, 127);//turning right?
    }
  }
  if (front <= 7){//backup and turn left
    backupAndTurnLeft(); 
  }

}

void backupAndTurnLeft(){

//run motors backward
  digitalWrite(12,1);
  digitalWrite(13,1);
  analogWrite(3, 127);
  analogWrite(11, 127);
  delay(500);
  digitalWrite(12,0);
  digitalWrite(13,0);
//turnleft
  analogWrite(3, 127);
  analogWrite(11, 0);
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
