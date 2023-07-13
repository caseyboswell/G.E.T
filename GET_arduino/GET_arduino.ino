//www.elegoo.com
//2016.12.08

// ON/OFF Switch
const int buttonPin = 9;    // the number of the pushbutton pin
bool ON = false;         // the current state of the output pin (initially OFF)
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Ultrasonic Sensor Library
#include "SR04.h"

// Chest Ultrasonic Sensor
#define ULTRASONIC_TRIG_PIN 13
#define ULTRASONIC_ECHO_PIN 12
SR04 ultrasonic_sensor = SR04(ULTRASONIC_ECHO_PIN, ULTRASONIC_TRIG_PIN);
long chest_distance;

// Controls
int PUSH_UP_DISTANCE = 10; // cm
int SQUAT_KNEE_ANGLE = 90; // degrees

void setup() {

  // ON/OFF Switch
  pinMode(buttonPin, INPUT);
  
  // Serial Monitor
  Serial.begin(9600);
  delay(1000);
}

void loop() {

  // Detect ON/OFF button press
  checkForButtonPress();

  if (ON) {
    
    // Collect & record chest distance measure
    chest_distance = ultrasonic_sensor.Distance();
//    printSensorValues();

    // Collect & record knee joint angles

    
  }
}


// Helper Functions

void printSensorValues() {
    Serial.print("Chest distance  = ");
    Serial.print(chest_distance);
    Serial.print("cm");
//    Serial.print(", ");
//    Serial.print("Other = ");
//    Serial.print(...);
//    Serial.println("cm");
    delay(10);
}

void checkForButtonPress() {
  
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == HIGH) {
        ON = !ON; // Switch the ON/OFF state
      }
    }
  }
  
  lastButtonState = reading;
}
