/*
* TTBOUNCE
 * Version 1.0 January, 2014
 * Copyright 2009 TOLDO TECHNIK
 * For details, see https://github.com/TOLDOTECHNIK/TTLED
 */

#include "TTBOUNCE.h"

TTBOUNCE::TTBOUNCE(uint8_t pin){
  _pin = pin;
  pinMode(_pin, INPUT);
  setActiveHIgh();
  _debounceInterval = DEFAULT_DEBOUNCE_INTERVAL;
  _previousMillis = millis();
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



void TTBOUNCE::update(){
  uint8_t state = digitalRead(_pin);


  if (state != _currentPinUnstableState){
    _previousMillis = millis();
  }
  else if(millis() - _previousMillis >= _debounceInterval){
    if (state != _currentPinState) {
      _currentPinState = state;
    }
  }

  _currentPinUnstableState = state;
}

uint8_t TTBOUNCE::read(){
  if(_activeHigh){
    return _currentPinState;
  }
  else{
    return !_currentPinState; 
  }
}


