//Demo for use of IR Distance sensor
int adc;
float voltage;

void setup(){
  pinMode(A0, INPUT);//sets up pin for input
  Serial.begin(9600);//sets up serial communications for display
}

void loop(){
  ADC = analogRead(A0);//read the analog voltage and convert to digital representation
  voltage = (ADC/1023.0)*5.0;//convert digital ADC value to voltage
  Serial.println(voltage);//display
  delay(100);//wait 100 milliseconds
}
