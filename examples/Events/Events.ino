#include <TTBOUNCE.h>


TTBOUNCE b = TTBOUNCE(3);          //create button instance and attach digital pin 3

void setup(){
  b.attachClick(click);			   //attach the click method to the click event
  b.attachDoubleClick(doubleClick);//attach the double click method to the double click event
  b.attachPress(press);			   //attach the press method to the press event
  
  Serial.begin(9600);
}


void loop(){
  b.update();
  
  Serial.print("state: ");
  Serial.print(b.read());
  
  Serial.print(" time: ");
  Serial.println(b.getHoldTime());
  
  delay(10);
}

void click(){
  Serial.println("Clicked");
}

void doubleClick(){
  Serial.println("Double clicked");
}

void press(){
  Serial.println("Long pressed");
}