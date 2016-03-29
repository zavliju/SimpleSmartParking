#define trigPin 8
#define echoPin 6
#define led 13

void setup() {
  Serial.begin (9600);
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
 

  if (distance <= 10) {
    digitalWrite(led, LOW);
    Serial.println("lagi ada mobil :-(");
}
  else {
    digitalWrite(led,HIGH);
  }

  if (distance > 10){
    Serial.println("Lagi kosong bro :-)");
  }
  else {
   // Serial.print(distance);
    Serial.println("Anda kurang beruntung");
   
  }
  delay(500);
}
