/*
 *  Adafruit_Trellis_XY.cpp
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
 */

#include <Adafruit_Trellis_XY.h>

// this array maps trellis IDs for a single Tile to X/Y coordinates
static byte trellisIDs[16][2] = {
	{ 0, 3 },
	{ 1, 3 },
	{ 2, 3 },
	{ 3, 3 },
	{ 0, 2 },
	{ 1, 2 },
	{ 2, 2 },
	{ 3, 2 },
	{ 0, 1 },
	{ 1, 1 },
	{ 2, 1 },
	{ 3, 1 },
	{ 0, 0 },
	{ 1, 0 },
	{ 2, 0 },
	{ 3, 0 }
};
		
// this array maps X/Y coordinates to single trellis Tile IDs
static byte XYTrellisIDs[4][4] = {
	{ 12, 13, 14, 15 },
	{  8,  9, 10, 11 },
	{  4,  5,  6,  7 },
	{  0,  1,  2,  3 }
};

//---------------------------------------------------------------
Adafruit_Trellis_XY::Adafruit_Trellis_XY(void) {

}

//---------------------------------------------------------------
Adafruit_Trellis_XY::~Adafruit_Trellis_XY(void) {
 	
}

//---------------------------------------------------------------
// initialize object with total number of Trellis keys
void Adafruit_Trellis_XY::begin(byte i_numKeys) {
	// initialize number of keys	
	numKeys = i_numKeys;
}

//---------------------------------------------------------------
// map Trellis button/led ids to X coordinates
byte Adafruit_Trellis_XY::getTrellisX(byte trellisID) {
	// get trellis matrix offsets
	if(trellisID < 16) {
		xOffset   = xOffsets[0];
	}
	else if(trellisID > 15 && trellisID < 32) {
		trellisID = trellisID - 16;
		xOffset   = xOffsets[1];
	}
	else if(trellisID > 31 && trellisID < 48) {
		trellisID = trellisID - 32;
		xOffset   = xOffsets[2];
	}  
	else if(trellisID > 47 && trellisID < 64) {
		trellisID = trellisID - 48;
		xOffset   = xOffsets[3];
	}
	else if(trellisID > 63 && trellisID < 80) {
		trellisID = trellisID - 64;
		xOffset   = xOffsets[4];
	}
	else if(trellisID > 79 && trellisID < 96) {
		trellisID = trellisID - 80;
		xOffset   = xOffsets[5];
	}  
	else if(trellisID > 95 && trellisID < 112) {
		trellisID = trellisID - 96;
		xOffset   = xOffsets[6];
	}
	else if(trellisID > 111 && trellisID < 128) {
		trellisID = trellisID - 112;
		xOffset   = xOffsets[7];
	}	
	else {
		xOffset   = xOffsets[0];
	}
	// add in offsets
	return trellisIDs[trellisID][0] + xOffset;
}

//---------------------------------------------------------------
// map Trellis button/led ids to Y coordinates
byte Adafruit_Trellis_XY::getTrellisY(byte trellisID) {	
	// get trellis matrix offsets
	if(trellisID < 16) {
		yOffset   = yOffsets[0];
	}
	else if(trellisID > 15 && trellisID < 32) {
		trellisID = trellisID - 16;
		yOffset   = yOffsets[1];
	}
	else if(trellisID > 31 && trellisID < 48) {
		trellisID = trellisID - 32;
		yOffset   = yOffsets[2];
	}  
	else if(trellisID > 47 && trellisID < 64) {
		trellisID = trellisID - 48;
		yOffset   = yOffsets[3];
	}
	else if(trellisID > 63 && trellisID < 80) {
		trellisID = trellisID - 64;
		yOffset   = yOffsets[4];
	}
	else if(trellisID > 79 && trellisID < 96) {
		trellisID = trellisID - 80;
		yOffset   = yOffsets[5];
	}  
	else if(trellisID > 95 && trellisID < 112) {
		trellisID = trellisID - 96;
		yOffset   = yOffsets[6];
	}
	else if(trellisID > 111 && trellisID < 128) {
		trellisID = trellisID - 112;
		yOffset   = yOffsets[7];
	}	
	else {
		yOffset   = yOffsets[0];
	}
	// add in offsets
	return trellisIDs[trellisID][1] + yOffset;    
}

//----------------------------------------------------------------------
// map X/Y coordinates to Trellis button/led ID
// (admittedly brute force but really simple. 
// Just pass ids to getTrellisX()/getTrellisY() until we get a match)
byte Adafruit_Trellis_XY::getTrellisId(byte xIn, byte yIn) {
  for(byte i = 0; i < numKeys + 1; i++) {
    if(getTrellisX(i) == xIn && getTrellisY(i) == yIn) {
      return i;
    }
  }
	// first Trellis ID or no match
  return 0;  
}
	
	