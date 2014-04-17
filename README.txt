/  
Adafruit_Trellis_XY.h

Copyright (C) 2014  George Kuetemeyer (gk@pobox.com)
   
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
   
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.
   
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

This is a library for the Adafruit Trellis PCB

Designed specifically to work with the Adafruit Trellis!
  ----> https://www.adafruit.com/products/1611
  ----> https://www.adafruit.com/products/1616
   
Version 1.2

INSTALLATION:

Adafruit_Trellis_XY is a library that can map one or more
Adafruit Trellises into a set of X/Y coordinates.

INSTALLATION:

Copy the "Adafruit_Trellis_XY folder to your "libraries" directory.

In the Arduino IDE, create a new sketch and select fromn the menu bar
"Sketch->import Library->Adafruit_Trellis_XY. Be sure to place
#include <Adafruit_Trellis_XY.h> at the top of your sketch along with
other required libraries ( <Adafruit_Trellis.h>, etc.).

-------------------------------------------------------------------------------------CREATION:

Adafruit_Trellis_XY trellisXY = Adafruit_Trellis_XY();

-------------------------------------------------------------------------------------METHODS:

void begin (byte number_of_keys) // set up trellisXY with total number of keys

void getTrellisX (byte trellisId) // get X coordinate for given trellis ID

void getTrellisY (byte trellisId) // get Y coordinate for given trellis ID

byte getTrellisId (byte xIn, byte yIn) // get Trellis ID for given X/Y coordinates
   
-------------------------------------------------------------------------------------
MAPPING TRELLIS TILE XY OFFSETS
   
In order for this library to function correctly, it's important that you
work out required X and Y offsets for each tile. Here is an example using
four tiles in a square (8X8 buttons/leds):
   
  -----
  |2|3|  <---- tile layout for 8X8 matrix
  |0|1|  
  -----
   
Given that layout, this code will set up things correctly, assuming you've
defined an object trellisXY:
   
trellisXY.xOffsets[0] = 0;
trellisXY.xOffsets[1] = 4;
trellisXY.xOffsets[2] = 0;
trellisXY.xOffsets[3] = 4;
trellisXY.yOffsets[0] = 0;
trellisXY.yOffsets[1] = 0;
trellisXY.yOffsets[2] = 4;
trellisXY.yOffsets[3] = 4;

Be sure to reflect this layout when you set up trellis.begin. In the case of
a 4X4 matrix you will want to arrange your tile addresses to match this layout.

  trellis.begin(0x70, 0x71, 0x72, 0x73);

If you haven't physically arranged the tiles that way, then rearrange the entries
in the begin statment. Here is how I had to address my 4X4 matrix:

  trellis.begin(0x72, 0x73, 0x70, 0x71);
   
Here's another example:
   
  ---------
  |0|1|2|3|  <------ tile layout for 4X8 matrix
  ---------
   
  
trellisXY.xOffsets[0] = 0;
trellisXY.xOffsets[1] = 4;
trellisXY.xOffsets[2] = 8;
trellisXY.xOffsets[3] = 12;
trellisXY.yOffsets[0] = 0;
trellisXY.yOffsets[1] = 0;
trellisXY.yOffsets[2] = 0;
trellisXY.yOffsets[3] = 0;
   
   
Here is simplest example for one Trellis
   
  ---
  |0|  <------ tile layout for single Trellis
  ---
   
trellisXY.xOffsets[0] = 0;
trellisXY.yOffsets[0] = 0;

-------------------------------------------------------------------------------------
SAMPLE CODE: 

#include <Wire.h>
#include <Adafruit_Trellis.h>
#include <Adafruit_Trellis_XY.h>

Adafruit_Trellis matrix0 = Adafruit_Trellis();
Adafruit_Trellis matrix1 = Adafruit_Trellis();
Adafruit_Trellis matrix2 = Adafruit_Trellis();
Adafruit_Trellis matrix3 = Adafruit_Trellis();

Adafruit_TrellisSet trellis =  Adafruit_TrellisSet(&matrix0, &matrix1, &matrix2, &matrix3);

Adafruit_Trellis_XY trellisXY = Adafruit_Trellis_XY();
#define NKEYS 64
#define NROWS 8
#define NCOLS 8

void setup() {
  // initialize trellis
  trellis.begin(0x72, 0x73, 0x70, 0x71);

  // initialize number of keys
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

  Serial.begin(9600);
}

void loop() {
  // clear leds
  trellis.clear();
  trellis.writeDisplay();
  // print out X/Y coordinates for all trellis IDs
  for(byte n = 0; x < trellisXY.numKeys; n++) {
    Serial.print(trellisXY.getTrellisX(n), DEC);
    Serial.print(" : ");
    Serial.println(trellisXY.getTrellisY(n), DEC);
    trellis.setLED(n);
    trellis.writeDisplay();
    delay(50);
  }
  //-----------------------------------------------------
  // do vertical bars
  trellis.clear();
  // print out trellis IDs for X/Y coordinates
  for(byte x = 0; x < NROWS; x++) {
    for(byte y = 0; y < NCOLS; y++) {
      Serial.print(x, DEC);
      Serial.print(": ");
      Serial.print(y, DEC);
      Serial.print(": ");
      Serial.println(trellisXY.getTrellisId(x, y));
      trellis.setLED(trellisXY.getTrellisId(x, y));
      trellis.writeDisplay();
      delay(50);
    }
  }
  //-----------------------------------------------------
  // do horizontal bars
  trellis.clear();
  // print out trellis IDs for X/Y coordinates
  for(byte y = 0; y < NCOLS; y++) {
    for(byte x = 0; x < NROWS; x++) {
      Serial.print(x, DEC);
      Serial.print(": ");
      Serial.print(y, DEC);
      Serial.print(": ");
      Serial.println(trellisXY.getTrellisId(x, y));
      trellis.setLED(trellisXY.getTrellisId(x, y));
      trellis.writeDisplay();
      delay(50);
    }
  }
}
