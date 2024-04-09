# An asynchronous detection library for pushbutton click events.

## Summary

This is a library for the Arduino IDE that helps listening to pushbutton click actions 
on an asynchronous and non-blocking way using callback functions. 

It can handle short, long and double clicks. 

It doesn't use delays, so it doesn't affect any other action on your code.  

<b>Important:</b> Do not use delay() on your code, or the button handling may be affected.

## Getting started

Use a normally-open momentary pushbutton connected to the pin you want to read.
It uses digitalRead() to detect whether the button is released (LOW) or pressed (HIGH) to detect button actions.

## How to use

Import the library:

~~~{.cpp}
#include <CallbackButton.h>
~~~

Create a CallbackButton object:

~~~{.cpp}
#define BUTTON_INPUT_PIN 5
CallbackButton callbackButton = CallbackButton(BUTTON_INPUT_PIN);
~~~

Create a function to be used as a callback (note the constants you can use for clickType values):

~~~{.cpp}
void onButtonClick(int port, int clickType) {
  // The port number and the detected clickType will be received as parameters.

  // Replace the code below with your own implementation.
  switch (clickType) {
    case CALLBACK_BUTTON_SHORT_CLICK:
      // SHORT_CLICK detected;
      break;
    case CALLBACK_BUTTON_LONG_CLICK:
      // LONG_CLICK detected;
      break;
    case CALLBACK_BUTTON_DOUBLE_CLICK:
      // DOUBLE_CLICK detected;
      break;
  }
}
~~~

Configure the port mode and the callback function in the setup() function:

~~~{.cpp}
void setup() 
{
  // Set the pin mode as INPUT. The lib won't do it on its own.
  pinMode(BUTTON_INPUT_PIN, INPUT);

  // Set the callback function, because it was not passed to callbackButton on the constructor.
  callbackButton.setCallbackFunction(onButtonClick);
}
~~~

In the loop() function, call the checkButtonState() method on the callbackButton instance:

~~~{.cpp}
void loop()
{
  callbackButton.checkButtonState();
}
~~~

Now every time the library detects any of its supported button click types (short, long or double click),
the callback function ```onButtonClick``` will be called.

<b>Note:</b> The times for long and double clicks detection and the debounce time can be configured,
check the other constructors and its parameters.

Check the ```examples``` folder for more working examples, including on how to listen to multiple buttons at once. 
