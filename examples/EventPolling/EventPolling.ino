#include <TTBOUNCE.h>

#define ANALOG_PIN_FOR_VIRTUAL_READING 0

TTBOUNCE b = TTBOUNCE(TTBOUNCE_WITHOUT_PIN); // create virtual button without hardware pin

void setup(){  
  Serial.begin(9600);
  b.enableDoubleClickEvent();                // ensure to activate double click detection if needed
  pinMode(ANALOG_PIN_FOR_VIRTUAL_READING, INPUT);
}

void loop(){
  b.update(analogRead(ANALOG_PIN_FOR_VIRTUAL_READING) < 100);
  
  switch (b.getLastDetectedEvent()) {
    case CLICK:
      Serial.println("click was detected");
      break;
    case DOUBLE_CLICK:
      Serial.println("double click was detected");
      break;
    case PRESS:
      Serial.println("press was detected");
      break;
  }
  
  delay(10);
}
