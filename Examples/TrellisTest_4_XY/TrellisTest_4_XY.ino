/*************************************************** 
  This is a test example for the Adafruit Trellis w/HT16K33 
  Added Adafruit_Trellis_XY library
  Print out X/Y values...
  
  G. Kuetemeyer
  03/20/2014
  gk@pobox.com


  Designed specifically to work with the Adafruit Trellis 
  ----> https://www.adafruit.com/products/1616
  ----> https://www.adafruit.com/products/1611

 ****************************************************/

#include <Wire.h>
#include <Adafruit_Trellis.h>
#include <Adafruit_Trellis_XY.h>

/*************************************************** 
  This example shows reading buttons and setting/clearing buttons in a loop
  Also sending X/Y values to serial port.

  Up to 8 matrices can be used but this example will show 4 or 1
 ****************************************************/

#define MOMENTARY 0
#define LATCHING 1
// set the mode here
#define MODE LATCHING 


Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_Trellis matrix1 = Adafruit_Trellis();
Adafruit_Trellis matrix2 = Adafruit_Trellis();
Adafruit_Trellis matrix3 = Adafruit_Trellis();

Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1, &matrix2, &matrix3);

#define NUMTRELLIS 4
#define NKEYS (NUMTRELLIS * 16)

Adafruit_Trellis_XY trellisXY = Adafruit_Trellis_XY();

#define INTPIN A2

//-----------------------------------------------------------

byte xyTrellisID;

//-----------------------------------------------------------
void setup() {
  Serial.begin(9600);
  Serial.println("Trellis X/Y Demo");

  // define number of keys
  trellisXY.begin(NKEYS);
  // set up x/y offsets
  trellisXY.xOffsets[0] = 0;
  trellisXY.xOffsets[1] = 4;
  trellisXY.xOffsets[2] = 0;
  trellisXY.xOffsets[3] = 4;
  trellisXY.yOffsets[0] = 0;
  trellisXY.yOffsets[1] = 0;
  trellisXY.yOffsets[2] = 4;
  trellisXY.yOffsets[3] = 4;  
  
  // INT pin requires a pullup
  pinMode(INTPIN, INPUT);
  digitalWrite(INTPIN, HIGH);
  
  // order is important here!! Start with tile address you want to
  // use as the first one, etc. Note that this will vary depending
  // on how you/ve set up addressing.
  trellis.begin(0x72, 0x73, 0x70, 0x71);

  // light up all the LEDs in order
  for (byte i=0; i < trellisXY.numKeys; i++) {
    trellis.setLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
  // then turn them off
  for (byte i=0; i < trellisXY.numKeys; i++) {
    trellis.clrLED(i);
    trellis.writeDisplay();    
    delay(50);
  }
}

void loop() {
  delay(30);  
  if (MODE == LATCHING) {
    // If a button was just pressed or released...
    if (trellis.readSwitches()) {
      // go through every button
      for (byte i=0; i < trellisXY.numKeys; i++) {
        byte xValue;
        byte yValue;
        byte xyTrellisID;
        // if it was pressed...
	if (trellis.justPressed(i)) {
          // print out X/Y values
          Serial.println("----------");
	  Serial.print("v"); Serial.println(i);
          // get x/y values
          xValue = trellisXY.getTrellisX(i);
          yValue = trellisXY.getTrellisY(i);
          Serial.print("x: "); Serial.println(xValue, DEC);
          Serial.print("y: "); Serial.println(yValue, DEC);
          // get Trellis ID from x/y values
          xyTrellisID = trellisXY.getTrellisId(xValue, yValue);
          Serial.print("xyTrellisID: "); Serial.println(xyTrellisID, DEC);
	  // Alternate the LED
	  if (trellis.isLED(i)) 
	    trellis.clrLED(i);
	  else
	    trellis.setLED(i);
        } 
      }
      // tell the trellis to set the LEDs we requested
      trellis.writeDisplay();
    }
  }
}

