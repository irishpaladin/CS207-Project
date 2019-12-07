# LED Cube with Clock

![ ](https://github.com/irishpaladin/LED-Cube-with-Clock/blob/master/img/finished.JPG)

This project came about because of my fascination with watching the [LED Cube tutorial](https://www.youtube.com/watch?v=2BlVUKW5hL0&t=27s) from Tapendra Mandal on YouTube. LED cube's primary purpose is to serve as a decoration. It is created in 
a way in which it lights up to different patterns.


## Repository Contents

- **/hardware** - Contains schematics and fritzing files
- **/img** - Contains image used for this README file
- **/src** - Contains the source code used in this project

## Materials Used
- Arduino UNO
- LED x64
- Resistor x4
- Thick Wires
- 2 Shift Registers
- 2 Buttons
- Digital clock
- Solder
- Soldering iron
- Breadboard or Prototyping Board 
- Wooden board
- Wood glue 
- Spray paint   

## Build Instructions
1. **I started by doing the 4x4x4 LED Cube.**

![schematic](https://github.com/irishpaladin/LED-Cube-with-Clock/blob/master/hardware/leds_schem.png)

The basic idea of the LED cube is that it has 64 LEDs design as a 4x4x4 cube. 
Every LEDs in horizontal layers contains 4x4 LEDs and has its anodes(+) connected by soldering it to a wire. These layers are stacked into each other to form a 4x4x4 cube.
After stacking, every vertically aligned LEDs should have their cathodes(-) connected using a wire with 1.5 inch extra wires at the bottom. 
After finishing, it should look like this:

![enter image description here](https://github.com/irishpaladin/LED-Cube-with-Clock/blob/master/img/LED-cube.JPG)

2. **Next is building the circuit**

![schematic](https://github.com/irishpaladin/LED-Cube-with-Clock/blob/master/hardware/body_schem.png)
The 16 cathode wires(vertical wires) will be connected to the output pins of the two shift registers while the four anode wires(horizontal wires) are connected to Arduino pins, as shown in the schematic.
Moreover, two buttons are connected to the Arduino pins and the other side to the ground. These two buttons will serve as the button for turning off the LED and for pattern changing. After this, you are now able to upload the course code and play around with the patterns.

![schematic](https://github.com/irishpaladin/LED-Cube-with-Clock/blob/master/img/initial-setup_no-clock.JPG)

3. **Integrating the clock**

You should find a clock that will be suitable for the LED cube. If you are not familiar with tinkering electronic devices(like me), it's preferred to find a clock that needs low voltage to run and has a fairly small circuit. Avoid clocks that have radio built-in as they have complicated circuits. Take note of the voltage the device needs and be sure not to put in too much. In this project, I used a clock that needs a 3AAA battery to run, which is 4.5V in total. I linked it's positive and negative to the 3.5v pin and ground of the Arduino, and it works

4. **Lastly, close up the lids!**

You now have a cool looking LED cube!
Check out my building process [here](https://youtu.be/bNUBpIrS2zI) .

## Usage
How the device work is pretty straight forward!

 1. Upload the code to the Arduino
 2. Play with the buttons and patterns
 3. Not satisfied with the patterns? Change / add patterns in the code! 
 4. Repeat and have fun!

## Credits
Tapendra Mandal with his [LED cube project](https://www.youtube.com/watch?v=2BlVUKW5hL0&t=27s) 
