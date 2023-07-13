//www.elegoo.com
//2016.12.08


// Libraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "SR04.h"
#include <string>

// ON/OFF Switch
const int buttonPin = 9;    // the number of the pushbutton pin
bool ON = false;         // the current state of the output pin (initially OFF)
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

// Chest Ultrasonic Sensor
#define ULTRASONIC_TRIG_PIN 26
#define ULTRASONIC_ECHO_PIN 25
SR04 ultrasonic_sensor = SR04(ULTRASONIC_ECHO_PIN, ULTRASONIC_TRIG_PIN);
long chest_distance;

// Controls
int PUSH_UP_DISTANCE = 20; // cm
int SQUAT_KNEE_ANGLE = 90; // degrees

// Wifi code by https://dronebotworkshop.com/esp32-intro/
const char *ssid = "GET";
WiFiServer server(80);

void setup() {

  // ON/OFF Switch
  pinMode(buttonPin, INPUT);
  
  // Serial monitor setup
  Serial.begin(115200);

  // Wifi server
  Serial.println("Configuring access point...");
  WiFi.softAP(ssid);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");
}

void loop() {

    Serial.println("test");
    delay(1000);

  // Detect ON/OFF button press
//  checkForButtonPress();

//  if (ON) {

    // Wifi Server
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
  
              // the content of the HTTP response follows the header:
//              client.print(HTML);
//              client.print(CSS);
//              client.print(SCRIPT);
  
              // The HTTP response ends with another blank line:
              client.println();
              // break out of the while loop:
              break;
            } else {    // if you got a newline, then clear currentLine:
              currentLine = "";
            }
          } else if (c != '\r') {  // if you got anything else but a carriage return character,
            currentLine += c;      // add it to the end of the currentLine
          }
  
          // Check to see if the client request was "GET /H" or "GET /L":
//          if (currentLine.endsWith("GET /H")) {
//            digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
//          }
//          if (currentLine.endsWith("GET /L")) {
//            digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
//          }
        }
      }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
    
    // Collect & record chest distance measure
    chest_distance = ultrasonic_sensor.Distance();
    if (chest_distance <  PUSH_UP_DISTANCE) {
      Serial.println("Pushup detected.");
      client.print("<script>pushup=true</script>");
    }
    printSensorValues();

    // Collect & record knee joint angles

    
//  }
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
