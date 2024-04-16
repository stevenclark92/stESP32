// Variable Declarations
// Clock signal input via pin 15
const int clockPin = 15;

// Pin 13 measures the state of the r/w output pin. Read is HIGH.
const int rwPin = 13; // Add your read/write pin number here

// Create arrays of pin for use by Addres & Data Buses
const int ABUS[] =  {2, 4, 5, 18, 19, 21, 22, 23};
const int DBUS[] = {12, 14, 27, 26, 25, 33, 32, 35};

// Pin 34 is available for future use

// Create volatile arrays to manage state of each bus between interrupts
volatile int abusState[8];
volatile int dbusState[8];

// Define base states of rw and clock inputs
volatile bool rwState = LOW;
volatile bool clockPulse = false;

// Interrupt handler that reads the pin states and sets a flag with each pulse
// Used two loops for cases where abus is 16 bits
void IRAM_ATTR handleInterrupt() {
  for (int n = 0; n < 8; n++) {
    abusState[n] = digitalRead(ABUS[n]);
  }
  for (int n = 0; n < 8; n++) {
    dbusState[n] = digitalRead(DBUS[n]);
  }
  rwState = digitalRead(rwPin); // Read the state of the read/write pin
  clockPulse = true; // Set the flag to indicate that a pulse has been detected
}

void setup() {

  Serial.begin(57600);

  pinMode(clockPin, INPUT);

  for (int n = 0; n < 8; n++) {
    pinMode(ABUS[n], INPUT);
  }

  for (int n = 0; n < 8; n++) {
    pinMode(DBUS[n], INPUT);
  }

  pinMode(rwPin, INPUT);

  attachInterrupt(digitalPinToInterrupt(clockPin), handleInterrupt, FALLING);

}

void printBinaryAndHexArray(volatile int* array, int size) {

  for (int i = 0; i < size; i++) {

    Serial.print(array[i]);

  }

  Serial.print(" ");

  for (int i = 0; i < size; i += 4) {

    int hexValue = 0;

    for (int j = 0; j < 4; j++) {
      hexValue <<= 1;
      hexValue |= array[i + j];
    }

    Serial.print(hexValue, HEX);

  }
}

void loop() {
  if (clockPulse) {

    printBinaryAndHexArray(abusState, 8);
    Serial.print(" | ");

    printBinaryAndHexArray(dbusState, 8);
    Serial.print(" | ");

    Serial.print(rwState == HIGH ? 'r' : 'w');

    Serial.println();
    
    clockPulse = false; // reset the flag
  }
}

