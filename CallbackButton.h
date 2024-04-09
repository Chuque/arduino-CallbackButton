#ifndef CallbackButton_h
#define CallbackButton_h

#include "Arduino.h"

#ifndef CALLBACK_BUTTON_SHORT_CLICK
#define CALLBACK_BUTTON_SHORT_CLICK 1
#endif

#ifndef CALLBACK_BUTTON_LONG_CLICK
#define CALLBACK_BUTTON_LONG_CLICK 2
#endif

#ifndef CALLBACK_BUTTON_DOUBLE_CLICK
#define CALLBACK_BUTTON_DOUBLE_CLICK 3
#endif

class CallbackButton {
  public:
    CallbackButton(int port);
    CallbackButton(int port, void (*callbackFunction)(int, int));
    CallbackButton(int port, int longClickTimeout, int doubleClickTimeout, int debounceTimeout);
    CallbackButton(int port, int longClickTimeout, int doubleClickTimeout, int debounceTimeout, void (*callbackFunction)(int, int));
	  void setCallbackFunction(void (*callbackFunction)(int, int));
    void checkButtonState();

  private:
    int _port;
    int _longClickTimeout;
    int _doubleClickTimeout;
    int _debounceTimeout;
    void (*_callbackFunction)(int, int);
    bool _isButtonPressed;
    bool _lastIsButtonPressed;
    bool _isLongClickCallbackCalled;
    unsigned long _buttonPressStartTime;
    unsigned long _timeSinceLastShortClick;
    unsigned long _lastDebounceTime;
};

#endif