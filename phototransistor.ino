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


float rightphototransistor;
float leftphototransistor;


unsigned const char leftmotor = 11;
unsigned const char rightmotor = 3;
unsigned const char fanmotor = 2;
unsigned const char fronttrigger = 7;
unsigned const char frontecho = 10;

int leftspeed;
int rightspeed;

float front;

void setup() {
  // put your setup code here, to run once:
  pinMode(A5, INPUT);

  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B-left
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel B pin

  pinMode(10, INPUT);//ultrasonics
  pinMode(7, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  leftphototransistor = analogRead(A5)/1024.0*5.0;
  rightphototransistor = analogRead(A4)/1024.0*5.0;

  if (rightphototransistor >= 0.1){
    extinguish();
  }
  if (leftphototransistor >= 0.1){
    rightspeed = 127;
    leftspeed = 0;
    analogWrite(leftmotor, leftspeed);
    analogWrite(rightmotor, rightspeed);
    delay(1000);
    extinguish();
  }

  leftspeed = 127;
  rightspeed = 127;

  analogWrite(leftmotor, leftspeed);
  analogWrite(rightmotor, rightspeed);
  
}


void extinguish(){
  while(1){
    if (front <= 5 && (rightphototransistor >= 0.2)){//time to extinguish the fire
      digitalWrite(9, HIGH);
      digitalWrite(8,HIGH);//stop moving
      digitalWrite(fanmotor, HIGH);//turn on fan 
    }

    if (leftphototransistor > rightphototransistor){
      leftspeed = 31;
      rightspeed = 63;
    }
    else if(leftphototransistor <= rightphototransistor){
      leftspeed = 63;
      rightspeed = 31;
    }
    analogWrite(leftmotor, leftspeed);
    analogWrite(rightmotor, rightspeed);
    
    leftphototransistor = analogRead(A5)/1024.0*5.0;
    rightphototransistor = analogRead(A4)/1024.0*5.0;
    front = ultrasonic(fronttrigger, frontecho);
  }
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
