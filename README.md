# TTBOUNCE

This is a debouncing button library for Arduino.

## History
2014-01-23 Initial release

## Installation
Download the ZIP file and extract it's content. Put the TTBOUNCE folder in "ARDUINOAPP/hardware/libraries/".
In the Arduino IDE you can test the sample sketches under Samples->TTBOUNCE.

## Usage
### Create TTBOUNCE object

####Parameters
pin: the number of the pin which is attached to the button/switch

####Returns
nothing

####Example
TTBOUNCE switch = TTLED(5);

### setActiveHigh()
When a switch is connected between a digital pin and VDD (5V) and the pin is pulled down over a resistor, the digital pin will be HIGH when the switch is pressed.
You can activate this behaviour by calling the setActiveHigh(). ActiveHigh is the default operation mode.

read() will return HIGH if switch is pressed and LOW if switch is released, no matter how the switch is attached to the digital pin.

####Parameters
none

####Returns
nothing

####Example
switch.setActiveHigh();

### setActiveLow()
When a switch is connected between a digital pin and GND and the pin is pulled up over a resistor, the digital pin will be LOW when the switch is pressed.
You can activate this behaviour by calling the setActiveLow().

read() will return HIGH if switch is pressed and LOW if switch is released, no matter how the switch is attached to the digital pin.

####Parameters
none

####Returns
nothing

####Example
switch.setActiveLow();

### setDebounceInterval(unsigned int interval)
Sets the time in which the debouncing happens. Default will be 10ms

Take a higher interval if there is digital noise on the pin.

####Parameters
interval: Debouncing time in ms

####Returns
nothing

####Example
switch.setDebounceInterval(200);

### enablePullup()
Activates the internal pull up resistor on the digital pin.

####Parameters
none

####Returns
nothing

####Example
switch.enablePullup();

### disablePullup()
Turns the internal pull up resistor off.

####Parameters
none

####Returns
nothing

####Example
switch.disablePullup();

### update()
Be sure to call this method over and over again. Place it somewhere in your loop routine. This will update the debouncing method and also the switch state.

####Parameters
none

####Returns
nothing

####Example
void loop(){
	switch.update();
}

### read()
This method will return the current switch status. HIGH if switch is pressed, LOW if switch is released.
Ensure to call the setActive... methods accordingly.

####Parameters
none

####Returns
HIGH = switch pressed
LOW = switch released

####Example
if(switch.read() == HIGH){	
	//turn led on
}

