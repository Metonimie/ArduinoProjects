
void writeDataToShiftRegister(int);

const int DATA  = 8;
const int LATCH = 9;
const int CLOCK = 10;

void setup() {
    pinMode(DATA, OUTPUT);
    pinMode(LATCH, OUTPUT);
    pinMode(CLOCK, OUTPUT);

    writeDataToShiftRegister(1);
}

void writeDataToShiftRegister(int data) {
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, MSBFIRST, B10101010);
    digitalWrite(LATCH, HIGH);
}

void loop() {
  

}
