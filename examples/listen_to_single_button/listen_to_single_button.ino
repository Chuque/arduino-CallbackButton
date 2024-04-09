#include <Arduino.h>
#include <SoftwareSerial.h>
#include <CallbackButton.h>

// Listen to a single button
// by Rafael Chuque <Rafa_chuque@hotmail.com>

// Demonstrates the easiest way to listen to a single button with the CallbackButton library

// Created 20 April 2024

#define BUTTON_INPUT_PIN 5 // Button you want to listen to.

CallbackButton callbackButton = CallbackButton(BUTTON_INPUT_PIN); // Create a CallbackButton instance.

void setup() 
{
  Serial.begin(9600);

  // Set the pin mode as INPUT. The lib won't do it on its own.
  pinMode(BUTTON_INPUT_PIN, INPUT);

  // Set the callback function, because it was not passed to callbackButton on the constructor.
  callbackButton.setCallbackFunction(onButtonClick);
}
 
void loop()
{
  // Call checkButtonState() for the callbackButton instance.
  callbackButton.checkButtonState();
}

void onButtonClick(int port, int clickType) {
  // The port number and the detected clickType will be received as parameters.

  // Replace the code below with your own implementation.
  Serial.print(port);
  switch (clickType) {
    case CALLBACK_BUTTON_SHORT_CLICK:
      Serial.println(" SHORT_CLICK");
      break;
    case CALLBACK_BUTTON_LONG_CLICK:
      Serial.println(" LONG_CLICK");
      break;
    case CALLBACK_BUTTON_DOUBLE_CLICK:
      Serial.println(" DOUBLE_CLICK");
      break;
  }
}