#define trigPin 13
#define echoPin 12

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(echoPin, INPUT);
}

long getDistanceInCm() {
  long duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  return distance;
}

void loop() {
  long distance = getDistanceInCm();
  if (distance < 10) {
    digitalWrite(5, 1);
    tone(4, 90);
  } else {
    digitalWrite(5, 0);
    noTone(4);
  }
  Serial.print(distance);
  Serial.println(" cm");
  delay(50);
} 
