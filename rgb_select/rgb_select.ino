/*
 * RGB State
 */

/* Pin deffinitions */
const int redPin    = 2;
const int greenPin  = 3;
const int bluePin   = 4;
const int buttonPin = 6;

enum state { OFF, R_ON, G_ON, B_ON, RG_ON, RB_ON, BG_ON, RGB_ON };

int lastButtonValue     = LOW;
int currentButtonValue  = LOW;
int currentLedState     = OFF;

/* Will light up the RGB */
void lightRGB(int r, int g, int b) {
  digitalWrite(redPin, r);
  digitalWrite(greenPin, g);
  digitalWrite(bluePin, b);  
};

boolean debounce(boolean last)
{
  boolean current = digitalRead(buttonPin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(buttonPin);
  }
  return current;
}

/* This will set the led's state according to the parameter */
void setLedState(int ledStateVal) {
  switch(ledStateVal) {
      case OFF:
        lightRGB(0, 0, 0);
        break;
      case R_ON:
        lightRGB(1, 0, 0);
        break;
      case G_ON:
        lightRGB(0, 1, 0);
        break;
      case B_ON:
        lightRGB(0, 0, 1);
        break;
      case RG_ON:
        lightRGB(1, 1, 0);
        break;
      case RB_ON:
        lightRGB(1, 0, 1);
        break;
      case BG_ON:
        lightRGB(0, 1, 1);
        break;
      case RGB_ON:
        lightRGB(1, 1, 1);
        break;
      default:
        Serial.println("Error in LED state change");
  }
}

void setup() {
  /* Initialize the serial connection */
  Serial.begin(9600);

  /* Set the output pins */
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  currentButtonValue = debounce(lastButtonValue);
  /* Execute this code when the button is pressed. */
  if (lastButtonValue == LOW && currentButtonValue == HIGH) {
    currentLedState = (currentLedState + 1) % 8;
    setLedState(currentLedState);
    Serial.print("Current led state: ");
    Serial.println(currentLedState);
  }
  lastButtonValue = currentButtonValue;
}
