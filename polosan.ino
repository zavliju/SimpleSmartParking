#define trigPin 12
#define echoPin 14
#define led 15

void setup() {
  Serial.begin (115200);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led, OUTPUT);
 
}

void loop() {
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
 

  if (distance <= 30) {
    digitalWrite(led, HIGH);
    Serial.println("Sisa 0 :-(");
}
  else {
    digitalWrite(led,LOW);
  }

  if (distance > 30){
    Serial.println("Sisa 1 :-)");
  }
  else {
   // Serial.print(distance);
    Serial.println("Anda kurang beruntung");
   
  }
  delay(500);
}
