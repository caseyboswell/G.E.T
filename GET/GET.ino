/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "GET"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "game.h"
#include "SR04.h"

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED
#define POT_PIN A0

// ON/OFF Switch
const int buttonPin = 9;    // the number of the pushbutton pin
bool ON = false;         // the current state of the output pin (initially OFF)
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Chest Ultrasonic Sensor
#define ULTRASONIC_TRIG_PIN 13
#define ULTRASONIC_ECHO_PIN 14
SR04 ultrasonic_sensor = SR04(ULTRASONIC_ECHO_PIN, ULTRASONIC_TRIG_PIN);
long chest_distance;

// Leg Potentiometer
int leg_angle;

// Controls
int PUSH_UP_DISTANCE = 20; // cm
int SQUAT_KNEE_ANGLE = 90; // degrees

// Set these to your desired credentials.
const char *ssid = "GET";
const char *password = "good";

WiFiServer server(80);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(POT_PIN, INPUT);

  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
//  WiFi.softAP(ssid, password);
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");
}

void loop() {
    

  // Collect & record chest distance measure
  chest_distance = ultrasonic_sensor.Distance();
  Serial.println(chest_distance);
  if (chest_distance <  PUSH_UP_DISTANCE) {
    Serial.println("Pushup detected.");
//      client.print("<script>pushup=true</script>");
  }
  printSensorValues();

// Collect & record leg angle
  int pot_value = analogRead(POT_PIN);
  leg_angle = map(pot_value, 0, 4096, 0, 300);
  if (leg_angle < 150) {
    //Serial.println("S Q U A T!!!!");
  }


  
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    
    while (client.connected()) {            // loop while the client's connected
      
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // The content of the HTTP response follows the header:
            client.print(HTML);
            client.print(CSS);
            client.print(JAVASCRIPT);

            // The HTTP response ends with another blank line:
            client.println();
            
            // break out of the while loop:
            //break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
          
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }

  delay(100);
}

// Helper Functions

void printSensorValues() {
    Serial.print("Chest distance  = ");
    Serial.print(chest_distance);
    Serial.print("cm");
    Serial.println();
//    Serial.print(", ");
//    Serial.print("Other = ");
//    Serial.print(...);
//    Serial.println("cm");
    delay(100);
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
