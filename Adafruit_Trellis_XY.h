/*
 *  Adafruit_Trellis_XY.h
 *  
 *  Copyright (C) 2014  George Kuetemeyer (gk@pobox.com)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *  ---
 *
 *  Version 1.2
 *
 *-----------------------------------------------------------
 * Mapping Trellis Tile XY offsets
 *
 * In order for this library to function correctly, it's important that you
 * work out required X and Y offsets for each tile. Here is an example using
 * four tiles in a square (8X8 buttons/leds):
 *
 * -----
 * |2|3|    <---- tile layout for 8X8 matrix
 * |0|1|    
 * -----
 *
 * Given that layout, this code will set up things correctly, assuming you've
 * defined an object trellisXY
 *
 * trellisXY.xOffsets[0] = 0;
 * trellisXY.xOffsets[1] = 4;
 * trellisXY.xOffsets[2] = 0;
 * trellisXY.xOffsets[3] = 4;
 * trellisXY.yOffsets[0] = 0;
 * trellisXY.yOffsets[1] = 0;
 * trellisXY.yOffsets[2] = 4;
 * trellisXY.yOffsets[3] = 4;
 *
 * Here's another example:
 *
 * ---------
 * |0|1|2|3|  <------ tile layout for 4X8 matrix
 * ---------
 *
 * 
 * trellisXY.xOffsets[0] = 0;
 * trellisXY.xOffsets[1] = 4;
 * trellisXY.xOffsets[2] = 8;
 * trellisXY.xOffsets[3] = 12;
 * trellisXY.yOffsets[0] = 0;
 * trellisXY.yOffsets[1] = 0;
 * trellisXY.yOffsets[2] = 0;
 * trellisXY.yOffsets[3] = 0;
 *
 *
 * Here is simplest example for one Trellis
 *
 * ---
 * |0|  <------ tile layout for single Trellis
 * ---
 *
 * trellisXY.xOffsets[0] = 0;
 * trellisXY.yOffsets[0] = 0;
 */

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

typedef uint8_t byte; 

class Adafruit_Trellis_XY {	
	public:
		Adafruit_Trellis_XY(void);	
		~Adafruit_Trellis_XY(void);
		void begin(byte i_numKeys);
		byte getTrellisId(byte xIn, byte yIn);	
		byte getTrellisX(byte trellisID);
		byte getTrellisY(byte trellisID);
		byte numKeys;		
		byte xOffsets[8];	
		byte yOffsets[8];
	private:
		byte xOffset;
		byte yOffset;	
};
