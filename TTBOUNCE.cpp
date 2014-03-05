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

void TTBOUNCE::setClickInterval(unsigned int interval){
  _clickInterval = interval;
}

void TTBOUNCE::setPressInterval(unsigned int interval){
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
    if (pinState != _currentPinState){
      _currentPinState = pinState;
      if(read()){
        _previousHighStateTime = millis();
      }
    }
  }
  _currentPinUnstableState = pinState;
  
  //states
  if (_state == 0){
    if (read() == HIGH){
      _state = 1;
      _timestamp = millis(); // remember starting time
    }
  } 
  else if (_state == 1){
    if (read() == LOW){
      _state = 2;
    } 
    else if ((read() == HIGH) && (millis() > _timestamp + _pressInterval)){
      if (_pressFunction) _pressFunction();
      _state = 4;
    }  
  } 
  else if (_state == 2){
    if (millis() > _timestamp + _clickInterval || (read() == LOW && !_doubleClickFunction)){
      if (_clickFunction) _clickFunction();
      _state = 0;
    } 
    else if (read() == HIGH){
      _state = 3;
    }
  } 
  else if (_state == 3){
    if (read() == LOW){
      if (_doubleClickFunction) _doubleClickFunction();
      _state = 0;
    }
  } 
  else if (_state == 4){
    if (read() == LOW){
      _state = 0;
    }
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
