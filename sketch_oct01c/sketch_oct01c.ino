#include <Wire.h>

  int address = 0x68;
  int error;
void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(9600);
  Serial.println("Intializing");



}

void loop() {
  // put your main code here, to run repeatedly:
   Wire.beginTransmission(address);
  error = Wire.endTransmission();
  Serial.print("Response: ");
  Serial.println(error);
}
