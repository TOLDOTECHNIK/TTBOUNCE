#ifndef TTBOUNCE_h
#define TTBOUNCE_h

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <Wprogram.h>
#endif

#define DEFAULT_DEBOUNCE_INTERVAL  10
#define DEFAULT_CLICK_INTERVAL 300
#define DEFAULT_PRESS_INTERVAL 1000

extern "C" {
  typedef void (*callbackFunction)(void);
}

class TTBOUNCE{
public:
  TTBOUNCE(uint8_t pin); 
  void setActiveHigh();
  void setActiveLow();
  void enablePullup();
  void disablePullup();
  void setDebounceInterval(unsigned int interval);
  void setPressInterval(unsigned int interval);
  void setClickInterval(unsigned int interval);
  void attachClick(callbackFunction function);
  void attachDoubleClick(callbackFunction function);
  void attachPress(callbackFunction function);
  void update(); 
  uint8_t read();
  unsigned long getHoldTime();

private:
  uint8_t _pin;
  uint8_t _activeHigh;
  uint8_t _state;
  uint8_t _currentPinState;
  uint8_t _currentPinUnstableState;
  
  callbackFunction _clickFunction;
  callbackFunction _doubleClickFunction;
  callbackFunction _pressFunction;

  unsigned long _timestamp;
  unsigned int _debounceInterval;
  unsigned int _clickInterval;
  unsigned int _pressInterval;
  unsigned long _previousHighStateTime;
};

#endif
