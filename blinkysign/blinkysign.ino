/*
  Blink
 Turns on an LED on for one second, then off for one second, repeatedly.
 
 This example code is in the public domain.
 
 To upload to your Gemma or Trinket:
 1) Select the proper board from the Tools->Board Menu
 2) Select USBtinyISP from the Tools->Programmer
 3) Plug in the Gemma/Trinket, make sure you see the green LED lit
 4) For windows, install the USBtiny drivers
 5) Press the button on the Gemma/Trinket - verify you see
 the red LED pulse. This means it is ready to receive data
 6) Click the upload button above within 10 seconds
 */
 #include <Adafruit_NeoPixel.h>
 #include "Sign.h"

Sign sign;

// the setup routine runs once when you press reset:
void setup() {
  sign.initialize();
  
  sign.startupSequence(Sign::CWWAVE); // FORJOHN: change the startup sequence
  sign.startupSequence(Sign::CELLCYCLE);
  sign.startupSequence(Sign::CCWWAVE);
  
  sign.setCellColor(TOPLEFT, 255, 0, 0); // FORJOHN: change the colors of the cells
  sign.setCellColor(TOPRIGHT, 0, 255, 0);
  sign.setCellColor(BOTTOMLEFT, 0, 255, 255);
  sign.setCellColor(BOTTOMRIGHT, 255, 0, 255);
}

// the loop routine runs over and over again forever:
void loop() {
  
}


