//www.elegoo.com
//2016.12.08

//// ON/OFF Switch
//const int buttonPin = 9;    // the number of the pushbutton pin
//bool ON = false;         // the current state of the output pin (initially OFF)
//int buttonState;             // the current reading from the input pin
//int lastButtonState = LOW;   // the previous reading from the input pin
//unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
//unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Ultrasonic Sensor Library
#include "SR04.h"

// Back Ultrasonic Sensor
#define BACK_TRIG_PIN 26
#define BACK_ECHO_PIN 25
SR04 back_sensor = SR04(BACK_ECHO_PIN, BACK_TRIG_PIN);
long back_distance;

//// Front Ultrasonic Sensor
//#define FRONT_TRIG_PIN 3
//#define FRONT_ECHO_PIN 2
//SR04 front_sensor = SR04(FRONT_ECHO_PIN, FRONT_TRIG_PIN);
//long front_distance;

//// DC Motor
//#define ENABLE 7
//#define DIRA 6
//#define DIRB 5
//float senseResistance = 1.5;

// Controls
//int RUN_DISTANCE = 10;
//int BRAKE_DISTANCE = 20;

void setup() {

//  // ON/OFF Switch
//  pinMode(buttonPin, INPUT);
  
//  // Set DC Motor Pin Direction
//  pinMode(ENABLE,OUTPUT);
//  pinMode(DIRA,OUTPUT);
//  pinMode(DIRB,OUTPUT);
//  pinMode(A0, INPUT);
  
  // Serial Monitor
  Serial.begin(115200);
  delay(1000);
}

void loop() {

//  // Detect ON/OFF button press
//  checkForButtonPress();
//
//  if (ON) {
    
    // Collect & record distance measure
    back_distance = back_sensor.Distance();
    Serial.println(back_distance);
//    front_distance = front_sensor.Distance();
//    printSensorValues();

//    // Check the motor current
//    // https://www.arduino.cc/en/Tutorial/BuiltInExamples/ReadAnalogVoltage
//    float sensorValueMax = 1023.0;
//    float motorVoltageSupply = 3.3;
//    int sensorValue = analogRead(A0);
//    float motorVoltage = sensorValue * (motorVoltageSupply / sensorValueMax); // Scaled between 0V and 3.3V
//    // V = IR -> I = V/R
//    float motorCurrent = motorVoltage / senseResistance;
//
////    Serial.print("sensorValue = ");
////    Serial.println(sensorValue);
//    Serial.print("motorVoltage = ");
//    Serial.println(motorVoltage);
//    Serial.print("motorCurrent = ");
//    Serial.println(motorCurrent);
//
//    // Turn the motor ON if:
//    // a threat is close to the backand no frontal obstacles are near.
//    if ((back_distance < RUN_DISTANCE) && (front_distance > BRAKE_DISTANCE)) {
//      motorON();
//    } else {
//      motorOFF();
//    }
//  }
}


// Helper Functions

//void printSensorValues() {
//    Serial.print("Back = ");
//    Serial.print(back_distance);
//    Serial.print("cm");
//    Serial.print(", ");
//    Serial.print("Front = ");
//    Serial.print(front_distance);
//    Serial.println("cm");
//    delay(10);
//}
//
//void motorON() {
////    Serial.println("Motor on");
//    digitalWrite(ENABLE,255); // enable full speed
//    digitalWrite(DIRA,HIGH); //one way
//    digitalWrite(DIRB,LOW);
//}
//
//void motorOFF() {
//  digitalWrite(ENABLE,LOW);
//}
//
//void checkForButtonPress() {
//  
//  int reading = digitalRead(buttonPin);
//
//  if (reading != lastButtonState) {
//    lastDebounceTime = millis();
//  }
//  
//  if ((millis() - lastDebounceTime) > debounceDelay) {
//    if (reading != buttonState) {
//      buttonState = reading;
//      if (buttonState == HIGH) {
//        ON = !ON; // Switch the ON/OFF state
//      }
//    }
//  }
//  
//  lastButtonState = reading;
//}
