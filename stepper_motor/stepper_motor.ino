#include <AccelStepper.h>
#define HALFSTEP 8

// Motor pin definitions
#define motorPin1  3     // IN1 on the ULN2003 driver 1
#define motorPin2  4     // IN2 on the ULN2003 driver 1
#define motorPin3  5     // IN3 on the ULN2003 driver 1
#define motorPin4  6     // IN4 on the ULN2003 driver 1

// Initialize with pin sequence IN1-IN3-IN2-IN4 for using the AccelStepper with 28BYJ-48
// AccelStepper::FULL4WIRE
// AccelStepper::FULL2WIRE
AccelStepper stepper1(AccelStepper::FULL4WIRE , motorPin1, motorPin3, motorPin2, motorPin4);

void setup() {
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(200.0);
  stepper1.setSpeed(500);
  stepper1.moveTo(20000);
  Serial.begin(9600);
}//--(end setup )---

void loop() {

  //Change direction when the stepper reaches the target position
//  if (stepper1.distanceToGo() == 0) {
//    stepper1.moveTo(-stepper1.currentPosition());
//  }
  Serial.println(stepper1.distanceToGo());
  Serial.println(stepper1.currentPosition());
  stepper1.run();
}
