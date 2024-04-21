//This code is a rough sketch. I would strongly advise against running with this in a prod environment.

const int buttonPin = 15; // Clock signal input via pin 15
const int ledPin = 2;    // LED indicator [using this as the clock input in practice]
// const int rwPin = 4; // Uncomment if needed

volatile bool buttonPressed = false; // Flag to indicate button press

// Interrupt Service Routine (ISR)
void IRAM_ATTR handleInterrupt() {
  buttonPressed = true; // Set the flag to indicate that a pulse has been detected
}

void setup() {
  Serial.begin(9600); // Initialize Serial communication
  pinMode(buttonPin, INPUT_PULLDOWN); // Configure button pin with pull-down
  pinMode(ledPin, OUTPUT); // Configure LED pin as output
  
  digitalWrite(ledPin, HIGH); // Initialize LED to HIGH

  attachInterrupt(digitalPinToInterrupt(buttonPin), handleInterrupt, FALLING); // Set interrupt on falling edge
}

void loop() {
  if (buttonPressed) { // Check if button was pressed
    Serial.println("Button pressed"); // Indicate button press in Serial monitor
    
    delay(250); // Hacky debounce delay - not an ideal way of doing things
    
    digitalWrite(ledPin, LOW); // Toggle LED off
    delayMicroseconds(5);
    digitalWrite(ledPin, HIGH); // Toggle LED on
    
    Serial.println(); // Blank line for readability

    delay(250); // Pause before resetting flag
    
    buttonPressed = false; // Reset the flag
  }
}