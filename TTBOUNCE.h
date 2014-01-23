#ifndef TTBOUNCE_h
#define TTBOUNCE_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <Wprogram.h>
#endif

#define DEFAULT_DEBOUNCE_INTERVAL  10

class TTBOUNCE{
public:
  TTBOUNCE(uint8_t pin); 
  void setActiveHigh();
  void setActiveLow();
  void enablePullup();
  void disablePullup();
  void setDebounceInterval(unsigned int interval); 
  void update(); 
  uint8_t read();

protected:
  uint8_t _pin;
  uint8_t _activeHigh;
  uint8_t _currentPinState;
  uint8_t _currentPinUnstableState;

  unsigned long _previousMillis;
  unsigned int _debounceInterval;
};

#endif


