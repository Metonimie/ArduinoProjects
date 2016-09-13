/*
Adafruit Arduino - Lesson 14. Sweep
*/

#include <Servo.h> 

int servoPin = 8;
 
Servo servo;  
 
int angle = 0;   // servo position in degrees 
 
void setup() 
{ 
  Serial.begin(9600);
  servo.attach(servoPin); 
  servo.write(0);
} 
 
 
void loop() 
{ 
//   scan from 0 to 180 degrees
  for(angle = 0; angle < 175; angle++)  
  {                                  
    servo.write(angle);               
    delay(20);                   
  } 
  delay(5000);
  // now scan back from 180 to 0 degrees
  for(angle = 170; angle > 0; angle--)    
  {                                
    servo.write(angle);
    if (angle == 100) { delay(1000); }           
    delay(20);       
  }
  delay(500);
//  while(1); 
//    int value = 0;
//    
//    while (Serial.available() > 0) { 
//      value = Serial.parseInt();
//      servo.write(value);
//    }
} 
