int trigPin = 7; // grey
int echoPin = 8; // purple
long duration,cm;

void setup() {
  Serial.begin(38400);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

void loop() {
 
  //set up the ultrasonic
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin,HIGH);

  cm = (duration/2) / 29.1;

  Serial.println(cm); 
  delay(600);


  
}
