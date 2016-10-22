void setup() {
  // put your setup code here, to run once:
  analogWriteResolution(12);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i = 0;
  for (i = 0; i < 4095; ++i) {
    analogWrite(DAC0, i);
    analogWrite(3, i);
  }
}
