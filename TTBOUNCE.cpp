/*
* TTBOUNCE
 * Version 1.0 January, 2014
 * Version 1.1 February, 2014
 * Copyright 2009 TOLDO TECHNIK
 * For details, see https://github.com/TOLDOTECHNIK/TTLED
 */

#include "TTBOUNCE.h"

TTBOUNCE::TTBOUNCE(uint8_t pin){
  _pin = pin;
  pinMode(_pin, INPUT);
  setActiveHigh();
  _debounceInterval = DEFAULT_DEBOUNCE_INTERVAL;
  _clickInterval = DEFAULT_CLICK_INTERVAL;
  _pressInterval = DEFAULT_PRESS_INTERVAL;
  _timestamp = millis();
}

void TTBOUNCE::setActiveHigh(){
  _activeHigh = true;
  _currentPinState = LOW;
}

void TTBOUNCE::setActiveLow(){
  _activeHigh = false;
  _currentPinState = HIGH;
}

void TTBOUNCE::enablePullup(){
  digitalWrite(_pin, HIGH);
}

void TTBOUNCE::disablePullup(){
  digitalWrite(_pin, LOW);
}

void TTBOUNCE::setDebounceInterval(unsigned int interval){
  _debounceInterval = interval; 
}

void TTBOUNCE::setClickInterval(unsigned int interval) {
  _clickInterval = interval;
}

void TTBOUNCE::setPressInterval(unsigned int interval) {
  _pressInterval = interval;
}

void TTBOUNCE::attachClick(callbackFunction function){
  _clickFunction = function;
}

void TTBOUNCE::attachDoubleClick(callbackFunction function){
  _doubleClickFunction = function;
}

void TTBOUNCE::attachPress(callbackFunction function){
  _pressFunction = function;
}

void TTBOUNCE::update(){
  uint8_t pinState = digitalRead(_pin);
  //debounce
  if (pinState != _currentPinUnstableState){
    _timestamp = millis();
  }
  else if(millis() - _timestamp >= _debounceInterval){
    if (pinState != _currentPinState) {
      _currentPinState = pinState;
      if(read()){
        _previousHighStateTime = millis();
      }
    }
  }
  _currentPinUnstableState = pinState;
  
  //states
  if (_state == 0) { // waiting for menu pin being pressed.
    if (read() == _activeHigh) {
      _state = 1; // step to state 1
      _timestamp = millis(); // remember starting time
    } // if

  } 
  else if (_state == 1) { // waiting for menu pin being released.
    if (read() == !_activeHigh) {
      _state = 2; // step to state 2

    } 
    else if ((read() == _activeHigh) && (millis() > _timestamp + _pressInterval)) {
      if (_pressFunction) _pressFunction();
      _state = 6; // step to state 6

    } 
    else {
      // wait. Stay in this state.
    } // if

  } 
  else if (_state == 2) { // waiting for menu pin being pressed the second time or timeout.
    if (millis() > _timestamp + _clickInterval) {
      // this was only a single short click
      if (_clickFunction) _clickFunction();
      _state = 0; // restart.

    } 
    else if (read() == _activeHigh) {
      _state = 3; // step to state 3
    } // if

  } 
  else if (_state == 3) { // waiting for menu pin being released finally.
    if (read() == !_activeHigh) {
      // this was a 2 click sequence.
      if (_doubleClickFunction) _doubleClickFunction();
      _state = 0; // restart.
    } // if

  } 
  else if (_state == 6) { // waiting for menu pin being release after long press.
    if (read() == !_activeHigh) {
      _state = 0; // restart.
    } // if
  }
}

uint8_t TTBOUNCE::read(){
  if(_activeHigh){
    return _currentPinState;
  }
  else{
    return !_currentPinState; 
  }
}

unsigned long TTBOUNCE::getHoldTime(){
  if(read()){
    return millis() - _previousHighStateTime;
  }
  else{
    return 0;
  }
}
