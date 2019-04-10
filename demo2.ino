//Demo for use of Ultrasonic Distance sensor
int trigPin = 11;
int echoPin = 12;
long distance;

void setup(){
  pinMode(trigPin, OUTPUT);//sets up pin for output
  pinMode(echoPin, INPUT);//sets up pin for input
  Serial.begin(9600);//sets up serial communications for display
}

void loop(){
  distance = ultrasonic(trigPin, echoPin);//call the written ultrasonic function
  Serial.println(distance);//display
  delay(100);//wait 100 milliseconds
}

long ultrasonic(int trigPin, int echoPin){
  //send trigger pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  //recieve echo pulse in milliseconds
  long duration = pulseIn(echoPin, HIGH);//sees how long pulse is high
  return duration/58;//return distance in cm
}
