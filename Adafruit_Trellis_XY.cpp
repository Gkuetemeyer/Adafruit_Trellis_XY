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
// set tile offsets
void Adafruit_Trellis_XY::setOffsets(byte tile_number, byte x_offset, byte y_offset) {
	offsets[tile_number][0] = x_offset;
	offsets[tile_number][1] = y_offset;	
}

//---------------------------------------------------------------
byte Adafruit_Trellis_XY::getTrellisX(byte trellisID) {
	return getOffsets(trellisID, 0);
}

//---------------------------------------------------------------
byte Adafruit_Trellis_XY::getTrellisY(byte trellisID) {
	return getOffsets(trellisID, 1);
}

//---------------------------------------------------------------
// map Trellis button/led ids to X coordinates
byte Adafruit_Trellis_XY::getOffsets(byte trellisID, byte x_or_y) {
	// get trellis matrix offsets
	if(trellisID < 16) {
		offset    = offsets[0][x_or_y];
	}
	else if(trellisID > 15 && trellisID < 32) {
		trellisID = trellisID - 16;
		offset    = offsets[1][x_or_y];
	}
	else if(trellisID > 31 && trellisID < 48) {
		trellisID = trellisID - 32;
		offset    = offsets[2][x_or_y];
	}  
	else if(trellisID > 47 && trellisID < 64) {
		trellisID = trellisID - 48;
		offset    = offsets[3][x_or_y];
	}
	else if(trellisID > 63 && trellisID < 80) {
		trellisID = trellisID - 64;
		offset    = offsets[4][x_or_y];
	}
	else if(trellisID > 79 && trellisID < 96) {
		trellisID = trellisID - 80;
		offset    = offsets[5][x_or_y];
	}  
	else if(trellisID > 95 && trellisID < 112) {
		trellisID = trellisID - 96;
		offset    = offsets[6][x_or_y];
	}
	else if(trellisID > 111 && trellisID < 128) {
		trellisID = trellisID - 112;
		offset    = offsets[7][x_or_y];
	}	
	else {
		offset   = offsets[0][x_or_y];
	}
	// add in offsets
	return trellisIDs[trellisID][x_or_y] + offset;
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

