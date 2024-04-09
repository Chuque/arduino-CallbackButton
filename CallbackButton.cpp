#include "Arduino.h"
#include "CallbackButton.h"

CallbackButton::CallbackButton(int port)
  : CallbackButton(port, [](){}) {
}

CallbackButton::CallbackButton(int port, void (*callbackFunction)(int, int))
  : CallbackButton(port, 500, 350, 10, callbackFunction) {
}

CallbackButton::CallbackButton(int port, int longClickTimeout, int doubleClickTimeout, int debounceTimeout)
  : CallbackButton(port, longClickTimeout, doubleClickTimeout, debounceTimeout, [](){}) {
}

CallbackButton::CallbackButton(int port, int longClickTimeout, int doubleClickTimeout, int debounceTimeout, void (*callbackFunction)(int, int))
  : _port(port), _longClickTimeout(longClickTimeout), _doubleClickTimeout(doubleClickTimeout), _debounceTimeout(debounceTimeout), _callbackFunction(callbackFunction) {
	_isButtonPressed = false;
	_lastIsButtonPressed = false;
	_isLongClickCallbackCalled = false;
	_buttonPressStartTime = NULL;
	_timeSinceLastShortClick = NULL;
	_lastDebounceTime = NULL;
}

void CallbackButton::setCallbackFunction(void (*callbackFunction)(int, int)) {
	_callbackFunction = callbackFunction;
}

void CallbackButton::checkButtonState() {
	unsigned long currentTime = millis();
  bool newIsButtonPressed = digitalRead(_port) == HIGH;

	if(_lastDebounceTime == NULL) {
		if(newIsButtonPressed != _lastIsButtonPressed) {
			_lastDebounceTime = currentTime;
		}
	} else {
		if((currentTime - _lastDebounceTime) > _debounceTimeout) {
			_isButtonPressed = newIsButtonPressed;
			_lastDebounceTime = NULL;
		}
	}

  if(_buttonPressStartTime == NULL) {
    if(_isButtonPressed) {
      //Button down
      _buttonPressStartTime = currentTime;
    }
  } else {
    if(_isButtonPressed) {
      if(!_isLongClickCallbackCalled && (currentTime - _buttonPressStartTime >= _longClickTimeout)) {
        //Button is being pressed long enough for a long click
        _callbackFunction(_port, CALLBACK_BUTTON_LONG_CLICK);
        _timeSinceLastShortClick = NULL;
        _isLongClickCallbackCalled = true;
      }
    } else {
      //Button up
      if(currentTime - _buttonPressStartTime < _longClickTimeout) {
        if(_timeSinceLastShortClick == NULL) {
          //_timeSinceLastShortClick is NULL, no previous short clicks were executed
          _timeSinceLastShortClick = currentTime;
        } else {
          //_timeSinceLastShortClick is NOT NULL, a short clicks were executed previously.
          //If _doubleClickTimeout has not been reached now, this is a double click.
          if(currentTime - _timeSinceLastShortClick < _doubleClickTimeout) {
            //DOUBLE_CLICK
            _callbackFunction(_port, CALLBACK_BUTTON_DOUBLE_CLICK);
            _timeSinceLastShortClick = NULL;
          }
        }
      }

      _buttonPressStartTime = NULL;
      _isLongClickCallbackCalled = false;
    }
  }

  if(!_isButtonPressed && _timeSinceLastShortClick != NULL && currentTime - _timeSinceLastShortClick >= _doubleClickTimeout) {
    //SHORT_CLICK
    _callbackFunction(_port, CALLBACK_BUTTON_SHORT_CLICK);
    _timeSinceLastShortClick = NULL;
  }

  _lastIsButtonPressed = _isButtonPressed;
}
