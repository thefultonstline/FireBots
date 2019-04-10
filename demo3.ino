//Demo for use of Arduino Motor Shield

/*
 * 
Function          Channel A   Channel B
Direction         Digital 12  Digital 13
Speed (PWM)       Digital 3   Digital 11
Brake             Digital 9    Digital 8
Current Sensing     Analog 0  Analog 1
 */

void setup(){
  //set up motor on channel A
  pinMode(12, OUTPUT);//sets up direction pin
  pinMode(9, OUTPUT);//sets up brake pin
  pinMode(3, OUTPUT);//sets up spped pin
}

void loop(){
  digitalWrite(12, HIGH);//set channel A to forward direction
  digitalWrite(9, LOW); //disengage the brake on channel A
  analogWrite(3, 255);//rotates motor on channel A forward at full speed(255/255)
  delay(5000);//motor will rotate for five seconds

  digitalWrite(9, HIGH); //engage the brake on channel A
  delay(1000);//motor will not rotate for one second

  digitalWrite(12, LOW);//set channel A to backward direction
  digitalWrite(9, LOW); //disengage the brake on channel A
  analogWrite(3, 127);//rotates motor on channel A backward at full speed(127/255)
  delay(5000);//motor will rotate for five seconds  

  digitalWrite(9, HIGH); //engage the brake on channel A
  delay(1000);//motor will not rotate for one second
}
