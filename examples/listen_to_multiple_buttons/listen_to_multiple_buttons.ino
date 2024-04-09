#include <Arduino.h>
#include <SoftwareSerial.h>
#include <CallbackButton.h>

// Listen to multiple buttons
// by Rafael Chuque <Rafa_chuque@hotmail.com>

// Demonstrates an easy way to listen to multiple buttons with the CallbackButton library

// Created 20 April 2024

// Buttons you want to listen to. Can be as many as you want.
#define BUTTON_A_INPUT_PIN 5
#define BUTTON_B_INPUT_PIN 6

const int buttonPins[] = {BUTTON_A_INPUT_PIN, BUTTON_B_INPUT_PIN};
const int BUTTON_PINS_ARRAY_SIZE = sizeof(buttonPins) / sizeof(buttonPins[0]);

CallbackButton* callbackButtons[BUTTON_PINS_ARRAY_SIZE];

void setup() 
{
  Serial.begin(9600);

  // Initialize CallbackButton instances
  for (int i = 0; i < BUTTON_PINS_ARRAY_SIZE; i++) {
    // Set the pin mode. The lib won't do it on its own.
    pinMode(buttonPins[i], INPUT);

    // Initialize each CallbackButton instance on the array.
    callbackButtons[i] = new CallbackButton(buttonPins[i], onButtonClick);
  }
}
 
void loop()
{ 
  for (int i = 0; i < BUTTON_PINS_ARRAY_SIZE; i++) {
    callbackButtons[i]->checkButtonState();  // On loop, we have to call checkButtonState() for all buttons we are handling.
  }
}

void onButtonClick(int port, int clickType) {
  // The port number and the detected clickType will be received as parameters, so you can use the same callback function for all buttons.

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