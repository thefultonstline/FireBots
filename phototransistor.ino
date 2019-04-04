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

long front;

void setup() {
  // put your setup code here, to run once:
  digitalWrite(fanmotor, LOW);
  pinMode(A5, INPUT);
  pinMode(A4, INPUT);

  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B-left
  pinMode(13, OUTPUT); //Initiates Motor Channel B pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel B pin

  digitalWrite(9,LOW);
  digitalWrite(8,LOW);//disengage brakes

  digitalWrite(12,0);
  digitalWrite(13,0);//direction

  Serial.begin(9600);
}

void loop() {
  rightphototransistor = (analogRead(A4))*5.0/1024.0;
  leftphototransistor = (analogRead(A5))*5.0/1024.0;

  
  Serial.print(leftphototransistor);
  Serial.print("\t");
  Serial.println(rightphototransistor);
  

  if (leftphototransistor >= 0.5 || rightphototransistor >= 0.5){
    if (leftphototransistor > rightphototransistor){
      analogWrite(rightmotor, 63);
      analogWrite(leftmotor, 31);
      Serial.println("Turn Left");
    }
    else if(rightphototransistor > leftphototransistor){
      analogWrite(rightmotor, 31);
      analogWrite(leftmotor, 63);
      Serial.println("Turn Right");
    }

    if (leftphototransistor >= 1.00 && rightphototransistor >= 1.00){
      digitalWrite(fanmotor, HIGH);
    }
  }
  delay(10);

}
