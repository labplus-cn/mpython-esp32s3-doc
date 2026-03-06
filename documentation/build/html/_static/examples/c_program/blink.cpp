/*
  Blink
  Turns an LED on for one second, then off for one second, repeatedly.
*/

#include <Arduino.h>

#define LED_BUILTIN 47 // Define the built-in LED pin, usually pin 13 on most boards

void setup() {
  // Initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);   // Turn the LED on
  delay(1000);                       // Wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // Turn the LED off
  delay(1000);                       // Wait for a second
}