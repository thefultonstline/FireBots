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
float rightturnvalue = 1.7;
float rightclose = 2.7;
float front;

unsigned const char fronttrigger = 7;
unsigned const char frontecho = 10;
unsigned const char leftmotor = 11;
unsigned const char rightmotor = 3;

int leftspeed;
int rightspeed;

int leftarrayindex;
int rightarrayindex;
float rightcurrent[100];
float leftcurrent[100];
float leftcurrenttotal = 0;
float rightcurrenttotal = 0;
float leftcurrentaverage;
float rightcurrentaverage;



void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B-left
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel B pin


  digitalWrite(9,LOW);
  digitalWrite(8,LOW);//disengage brakes

  digitalWrite(12,0);
  digitalWrite(13,0);//direction

  pinMode(A4, INPUT);//ir

  pinMode(10, INPUT);//ultrasonics
  pinMode(7, OUTPUT);

  pinMode(A1, INPUT);
  pinMode(A0, INPUT);
  
  Serial.begin(9600);


  for (int i = 0; i < 100; i++){
    rightcurrent[i] = 0.0;
    leftcurrent[i] = 0.0;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
   right = (analogRead(A4))*5.0/1024.0;
   front = ultrasonic(fronttrigger, frontecho);

   
   if (front <= 5 || stuck()){
        backupAndTurnLeft();
        arrayclear();
    }

   Serial.print(leftcurrentaverage);
   Serial.print(" ");
   Serial.println(rightcurrentaverage);

   if (front > 20){
    if (right < rightturnvalue){
      //turn right
      leftspeed = 127;
      rightspeed = 31;
    }
    else if(right > rightclose){//too close to right wall-lean to the left
      leftspeed = 95;
      rightspeed = 127;      
    }
    else{//go straight if comfortable distance from wall
      leftspeed = 127;
      rightspeed = 127;
    }
    analogWrite(leftmotor, leftspeed);
    analogWrite(rightmotor, rightspeed);
   }

   else if (front <= 20 && front > 5){ //front is <20 -too close to wall
    if (right < rightturnvalue){
      //check if we are already turning right
      leftspeed = 127;
      rightspeed = 31;
      analogWrite(leftmotor, leftspeed);
      analogWrite(rightmotor, rightspeed);
    }
    else{//not turning right      
      leftspeed = 0;
      rightspeed = 127;
      analogWrite(leftmotor, leftspeed);
      analogWrite(rightmotor, rightspeed);
     // delay(500);
    }
    
   } 
  
}

void arrayclear(){
  for (int i = 0; i <100; i++){
    leftcurrent[i] = 0;
    rightcurrent[i] = 0;
  }
  leftcurrenttotal = 0;
  rightcurrenttotal = 0;
}

bool stuck(){

   float temp;

   temp = analogRead(A1)/1024.0*5.0/1.65;

   if (temp >= 0){
    leftcurrenttotal -= leftcurrent[leftarrayindex];  
    leftcurrent[leftarrayindex] = temp;
    leftcurrenttotal += leftcurrent[leftarrayindex];
    leftarrayindex++;
   }

   temp = analogRead(A0)/1024.0*5.0/1.65;
   
   
   if (temp >= 0){
    rightcurrenttotal -= rightcurrent[rightarrayindex];  
    rightcurrent[rightarrayindex] = temp;
    rightcurrenttotal += rightcurrent[rightarrayindex];
    rightarrayindex++;
   }
   
   if (leftarrayindex == 100){
    leftarrayindex = 0;
   }
   if (rightarrayindex == 100){
    rightarrayindex = 0;
   }

   leftcurrentaverage =  leftcurrenttotal/100.0;
   rightcurrentaverage = rightcurrenttotal/100.0;

   return rightcurrentaverage >= 0.4 || leftcurrentaverage >= 0.4;
}


void backupAndTurnLeft(){

//run motors backward
  //run motors backward
  digitalWrite(12,1);
  digitalWrite(13,1);

  leftspeed = 127;
  rightspeed = 127;
  analogWrite(rightmotor, rightspeed);
  analogWrite(leftmotor, leftspeed);

  delay(500);

  //change back to forward
  digitalWrite(12,0);
  digitalWrite(13,0);
//turnleft
  leftspeed = 0;
  rightspeed = 127;
  analogWrite(rightmotor, rightspeed);
  analogWrite(leftmotor, leftspeed);
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
