
/*
 * Date:   02.09.2016
 * Author: Denis Nutiu
 */
#define POTENTIOMETER_PIN 0
#define LED_PIN 11

int potentiometer_value;

void setup() {
    Serial.begin(9600);
    Serial.println("Initialized");
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
  potentiometer_value = analogRead(POTENTIOMETER_PIN) / 4;
  potentiometer_value = constrain(potentiometer_value, 0, 255);
  Serial.println(potentiometer_value);
  analogWrite(LED_PIN, potentiometer_value);
  delay(10);
}
