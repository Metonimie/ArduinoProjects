void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

int val;
void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(A0);
  val = map(val, 553, 630, 0, 255);
  val = constrain(val, 0, 255);
  Serial.println(val);
  delay(100);
}
