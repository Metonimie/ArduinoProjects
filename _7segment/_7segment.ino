
/*
 * Name:   Seven-Segment Display Demo
 * Date:   02.09.2016
 * Author: Denis Nutiu
 */
#define PINS_IN_USE 8

/* Pin are from dot to a,b,c,d,e,f,g */
const int PIN_ARRAY[8] = {2, 3, 4, 5, 6, 7, 8, 9};
const int DIGITS[16]   = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 
                          0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

void setup() {
    for (int i = 0; i < PINS_IN_USE; ++i) {
        pinMode(PIN_ARRAY[i], OUTPUT);
    }
}

void setAll(unsigned value) {
    for (unsigned i = 1; i < PINS_IN_USE; ++i) {
        digitalWrite(PIN_ARRAY[i], value);
    }   
}

void setDot(unsigned value) {
    digitalWrite(PIN_ARRAY[0], value);  
}

void showDigit(unsigned digit) {
    unsigned value;
    for (unsigned i = 1u, j = 1; j < 8; i <<= 1, ++j) {
        value = (i & DIGITS[digit]) ? HIGH : LOW;
        digitalWrite(PIN_ARRAY[j], value);
    }
}

void loop() {
   setDot(HIGH);
   for (int i = 0; i < 16; ++i) {
      showDigit(i);
      delay(1000); 
   }
}
