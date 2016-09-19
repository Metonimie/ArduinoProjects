#include <ir_Lego_PF_BitStreamEncoder.h>
#include <IRremote.h>
#include <IRremoteInt.h>

// Shift Register Settings
const int DATA  = 8;
const int LATCH = 9;
const int CLOCK = 10;

// IR Remote Settings
const int RECV_PIN = 11;
IRrecv irrecv(RECV_PIN);
decode_results results;

// Controls which leds will be on, by limiting the choices.
enum led_state { 
    s0 = B00000000,
    s1 = B10000000,
    s2 = B11000000,
    s3 = B11100000,
    s4 = B11110000,
    s5 = B11111000,
    s6 = B11111100,
    s7 = B11111110,
    s8 = B11111111
};

// Function declarations
void writeDataToShiftRegister(led_state);
byte getState(int);

// Variables
int currentLEDState = 0;

void setup() {
    pinMode(DATA, OUTPUT);
    pinMode(LATCH, OUTPUT);
    pinMode(CLOCK, OUTPUT);

    Serial.begin(9600); // Start serial communication with 9600 baud-rate.
    Serial.println("Initializing...");
    
    writeDataToShiftRegister(s0); // Turn off leds
    irrecv.enableIRIn(); // Start the receiver

    Serial.println("Initialization done.");
}

/* Returns the state based on an integer */
byte getState(int state) {
  byte return_value = s0;
  switch (state) {
    case 0:
      return_value = s0;
      break;
    case 1:
      return_value = s1;
      break;
    case 2:
      return_value = s2;
      break;
    case 3:
      return_value = s3;
      break;
    case 4:
      return_value = s4;
      break;
    case 5:
      return_value = s5;
      break;
    case 6:
      return_value = s6;
      break;
    case 7:
      return_value = s7;
      break;
    case 8:
      return_value = s8;
      break;
    default:
      Serial.println("getState: Error! Invalid state received");
  }

  Serial.print("getState: Received ");
  Serial.print(state);
  Serial.print(" returning ");
  Serial.println(return_value, BIN);

  return return_value;
}

/* Shifts out the data to the register, accepts only byte from the led_state enum */
void writeDataToShiftRegister(led_state state) {
    Serial.print("writeDataToShiftRegister: Sent:");
    Serial.println(state, BIN);
    
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, LSBFIRST, state);
    digitalWrite(LATCH, HIGH);
}

void handleSignal(int signal) {
    Serial.print("handleSignal: Handling: ");
    Serial.println(signal, HEX);

    /*  This block will be used to handle
     *  events if the button is held for longer time.
     */
    static int lastSignal = 0;
    if (signal != 0xFFFFFFFF) {
        lastSignal = signal; 
    } else if ( signal == 0xFFFFFFFF) {
        signal = lastSignal;
    }

    // Update the LED state accordingly.
    switch(signal) {
        case 0xFFE01F: // minus button
          // Check if current led state is 0, if it is, set it to 8 else decrement.
          currentLEDState = currentLEDState - 1 < 0 ? 8 : currentLEDState - 1;
          writeDataToShiftRegister(getState(currentLEDState));
          break;
        case 0xFFA857: // plus button
          currentLEDState = (currentLEDState + 1) % 9; // reset on overflow
          writeDataToShiftRegister(getState(currentLEDState));
          break;
        case 0xFF6897: // zero
          currentLEDState = 0;
          writeDataToShiftRegister(getState(0));
          break;
        case 0x30CF: // one
          currentLEDState = 1;
          writeDataToShiftRegister(getState(1));
          break;
        case 0x18E7: // two
          currentLEDState = 2;
          writeDataToShiftRegister(getState(2));
          break;
        case 0x7A85: // three
          currentLEDState = 3;
          writeDataToShiftRegister(getState(3));
          break;
        case 0x10EF: // four
          currentLEDState = 4;
          writeDataToShiftRegister(getState(4));
          break;
        case 0x38C7: // five
          currentLEDState = 5;
          writeDataToShiftRegister(getState(5));
          break;
        case 0x5AA5: // six
          currentLEDState = 6;
          writeDataToShiftRegister(getState(6));
          break;
        case 0x42BD: // seven
          currentLEDState = 7;
          writeDataToShiftRegister(getState(7));
          break;
        case 0x4AB5: // eight
          currentLEDState = 8;
          writeDataToShiftRegister(getState(8));
          break;
        default:
          Serial.print("handleSignal: Error! Cannot handle: ");
          Serial.println(signal, HEX);
    }
}

void loop() {
    // Capture received signals and decode them.
    if (irrecv.decode(&results)) {
       Serial.print("Received signal: ");
       Serial.println(results.value, HEX);
       handleSignal(results.value);
       delay(10); // wait 10ms   
       irrecv.resume(); // Receive the next value
    }
}
