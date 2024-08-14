const int ledPin = LED_BUILTIN; // Built-in LED on Arduino Nano 33 IoT
const int buttonPin = 2;        // Pin connected to the push button
const int dashDuration = 700;   // Duration of a dash
const int dotDuration = 250;    // Duration of a dot
const int letterDelay = 1000;   // Delay between letters
const int wordDelay = 2000;     // Delay before starting the name again

// Morse code for "Priyanshu"
String morseCode[] = 
{
  ".--.",  // P
  ".-.",   // R
  "..",    // I
  "-.--",  // Y
  ".-",    // A
  "-.",    // N
  "...",   // S
  "....",  // H
  "..-"    // U
};

// Button state variable
bool buttonPressed = false;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Use internal pull-up resistor for button
}

void loop() {
  int buttonState = digitalRead(buttonPin);

  if (buttonState == LOW) { // Button pressed
    buttonPressed = true;
  }

  if (buttonPressed) {
    digitalWrite(ledPin, HIGH); // Turn on LED to indicate start
    delay(wordDelay);           // Wait before starting Morse code

    // Loop through each letter in "Priyanshu"
    for (int i = 0; i < 9; i++) { 
      blinkMorseCode(morseCode[i]);
      delay(letterDelay); // Pause between letters

      // Check if the button is pressed again to restart the sequence
      if (digitalRead(buttonPin) == LOW) {
        buttonPressed = false;
        return; // Exit the loop and restart from the beginning
      }
    }

    delay(wordDelay); // Wait before starting the sequence again
    buttonPressed = false; // Reset the button press state
  }
}

// Function to blink Morse code for a given letter
void blinkMorseCode(String code) {
  for (int i = 0; i < code.length(); i++) {
    if (code[i] == '.') {
      blinkDot();
    } else if (code[i] == '-') {
      blinkDash();
    }
    delay(dotDuration); // Pause between dots and dashes in the same letter
  }
}

// Function to blink a dot
void blinkDot() {
  digitalWrite(ledPin, HIGH); 
  delay(dotDuration);
  digitalWrite(ledPin, LOW);
  delay(dotDuration);
}

// Function to blink a dash
void blinkDash() {
  digitalWrite(ledPin, HIGH);
  delay(dashDuration);
  digitalWrite(ledPin, LOW);
  delay(dotDuration);
}
