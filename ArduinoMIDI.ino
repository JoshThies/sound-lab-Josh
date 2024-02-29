
// Board: "Sparkfun Pro Micro
// ** caution! Select correct voltage in the IDE or you will brick the microcontroller! **
// Tools ... Processor ... (3.3v or 5v)
// see: https://learn.sparkfun.com/tutorials/pro-micro--fio-v3-hookup-guide/troubleshooting-and-faq

// No MIDI - for testing the buttons, pot, and speaker

// #include "pitches.h" just need these 3 pitches for this demo:

#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330

// LED connections
#define RED_LED_PIN 16
#define GREEN_LED_PIN 15
#define BLUE_LED_PIN 14

// Button connections
#define RED_BUTTON 9
#define GREEN_BUTTON 8
#define BLUE_BUTTON 7

#define SPEAKER 2
#define NOTEDURATION 200  // milliseconds

// potentiometer
#define POT_PIN A0
int controller = 0;         // new controller input value
int controller_prev = 0;    // previous controller input value
#define CONTROLLER_DELTA 4  // update controller if new value is +/- different from prev

#define MIDI_CHANNEL 0  // actual channel - 1
#define RED_NOTE 64     // https://newt.phys.unsw.edu.au/jw/notes.html
#define GREEN_NOTE 62
#define BLUE_NOTE 60

void setup() {
  Serial.begin(9600);

  // initialize LED pins as output.
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);

  // initialize Button pins as inputs; pressing buttons connect pin to ground
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
  pinMode(BLUE_BUTTON, INPUT_PULLUP);

  //Blink an LED
  digitalWrite(RED_LED_PIN, HIGH);  // LED on
  delay(1000);
  digitalWrite(RED_LED_PIN, LOW);  // LED off

  //  while (!Serial) {
  //    ; // wait for serial port to connect.
  //  }
  Serial.println(F(__FILE__));  // print the name of this file
}

void loop() {
  // poll for button presses
  if (digitalRead(RED_BUTTON) == LOW) {
    Serial.println("Red button");
    digitalWrite(RED_LED_PIN, HIGH);          // LED on
    tone(SPEAKER, NOTE_E4 + controller);
    delay(100);                               // button debounce
    while (digitalRead(RED_BUTTON) == LOW) {  //wait for button to be released
    }
    digitalWrite(RED_LED_PIN, LOW);       // LED off
    noTone(SPEAKER);
  }

  if (digitalRead(GREEN_BUTTON) == LOW) {
    Serial.println("Green button");
    digitalWrite(GREEN_LED_PIN, HIGH);          // LED on
    tone(SPEAKER, NOTE_D4 + controller);
    delay(100);                                 // button debounce
    while (digitalRead(GREEN_BUTTON) == LOW) {  //wait for button to be released
    }
    digitalWrite(GREEN_LED_PIN, LOW);       // LED off
    noTone(SPEAKER);
  }

  if (digitalRead(BLUE_BUTTON) == LOW) {
    Serial.println("Blue button");
    digitalWrite(BLUE_LED_PIN, HIGH);          // LED on
    tone(SPEAKER, NOTE_C4 + controller);
    delay(100);                                // button debounce
    while (digitalRead(BLUE_BUTTON) == LOW) {  //wait for button to be released
    }
    digitalWrite(BLUE_LED_PIN, LOW);       // LED off
    noTone(SPEAKER);
  }

  //check for controller input potentiometer value change
  // read the analog in value:
  controller = map(analogRead(POT_PIN), 0, 1023, -200, 1000);
  if (abs(controller - controller_prev) >= CONTROLLER_DELTA) {
    Serial.print("controller = ");
    Serial.println(controller);
    controller_prev = controller;
  }
}
