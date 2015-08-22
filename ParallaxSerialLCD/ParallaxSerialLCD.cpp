/*
The MIT License (MIT)

Copyright (c) 2012-2013 Megatome Technologies, LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <SoftwareSerial.h>
#include "ParallaxSerialLCD.h"

#define PINOUT      0
#define BOUNCE      1
#define NUMROWS     2
#define NUMCOLS     3

#define WRITE_BASE 	128
// The cursor position for 16 column and 20 column displays uses the same address
// The 16 column display just doesn't show the last 4 columns
#define COL_SIZE    20

ParallaxLCD::ParallaxLCD ( int pin, int numRows, int numCols) : SoftwareSerial(pin,pin) {
	_bv[PINOUT]=pin;
	_bv[BOUNCE]=10;
	_bv[NUMROWS]=numRows;
	_bv[NUMCOLS]=numCols;
}

void ParallaxLCD::setup(boolean startEmpty ) {
	pinMode(_bv[PINOUT], OUTPUT);
	delay(_bv[BOUNCE]);
	begin(19200);
	delay(_bv[BOUNCE]);
	if (startEmpty) {
		clear();
	}
	noCursor();
}

void ParallaxLCD::display () {
	write(24); delay(_bv[BOUNCE]);
}

void ParallaxLCD::noDisplay () {
	write(21); delay(_bv[BOUNCE]);
}

void ParallaxLCD::scrollDisplayLeft () {
	print(8); delay(_bv[BOUNCE]);
}

void ParallaxLCD::scrollDisplayRight () {
	write(9); delay(_bv[BOUNCE]);
}

void ParallaxLCD::clear () {
	write(12); delay(_bv[BOUNCE]*10);
}

void ParallaxLCD::cursor () {
	write(24); delay(_bv[BOUNCE]);
}

void ParallaxLCD::blink () {
	write(23); delay(_bv[BOUNCE]);
}

void ParallaxLCD::noBlink () {
	write(22); delay(_bv[BOUNCE]);
}

void ParallaxLCD::noCursor () {
	write(22); delay(_bv[BOUNCE]);
}

void ParallaxLCD::cursorOnChrBlink () {
	write(25); delay(_bv[BOUNCE]);
}

void ParallaxLCD::cr () {
	write(13); delay(_bv[BOUNCE]);
}

void ParallaxLCD::lf () {
	write(10); delay(_bv[BOUNCE]);
}

void ParallaxLCD::backlight () {
	write(17); delay(_bv[BOUNCE]);
}

void ParallaxLCD::noBacklight () {
	write(18); delay(_bv[BOUNCE]);
}

/**
 * Duration: 208 - 214 (1/64th note - 1 whole note[2 secs])
 * Scale   : 215 - 219 (3rd - 7th scale)
 * Note    : 220 - 232 (A, A#, B, etc..., F#, F, G#)
 */
void ParallaxLCD::playTone(int duration, int scale, int note) {

	duration = constrain(duration, 208, 214);
	scale = constrain(scale, 215, 219);
	note = constrain(note, 220, 232);

    write(scale);
    write(note);
    write(duration);
    delay(_bv[BOUNCE]);
}

/**
 * Set a custom character at the 'charIndex' index (0-7) with an
 *  array of bytes. Nominally, this will contain 8 bytes in it.
 */
void ParallaxLCD::createChar(int charIndex, byte bytes[]) {

   if(sizeof(bytes)/sizeof(bytes[0]) > 8) {
      return;
   }

   int index = constrain(charIndex, 0, 7);
   index = map(index, 0, 7, 248, 255);

   unsigned char *byte = bytes;

   write(index);
   for (int i=0; i < 8; i++) {
     write(byte[i]);
   }
   delay(_bv[BOUNCE]);
}

/**
 * Print whatever is stored in the custom character buffer.
 * If nothing is stored there, usually, nothing will print out.
 */
void ParallaxLCD::printCustomChar(int charIndex) {
   int index = constrain(charIndex, 0, 7);
   write(index);
   delay(_bv[BOUNCE]);
}

void ParallaxLCD::setCursor ( uint8_t col, uint8_t row )
{
	write(WRITE_BASE + (row * COL_SIZE) + col);
}

// shortcuts

void ParallaxLCD::at ( int row, int col, char v )				{ setCursor(col,row); print(v); }
void ParallaxLCD::at ( int row, int col, const char v[] )	{ setCursor(col,row); print(v); }
void ParallaxLCD::at ( int row, int col, String v )             { setCursor(col,row); print(v); }
void ParallaxLCD::at ( int row, int col, uint8_t v )			{ setCursor(col,row); print(v); }
void ParallaxLCD::at ( int row, int col, int v )				{ setCursor(col,row); print(v); }
void ParallaxLCD::at ( int row, int col, unsigned int v )	{ setCursor(col,row); print(v); }
void ParallaxLCD::at ( int row, int col, long v )				{ setCursor(col,row); print(v); }
void ParallaxLCD::at ( int row, int col, unsigned long v )	{ setCursor(col,row); print(v); }
void ParallaxLCD::at ( int row, int col, long v, int t )		{ setCursor(col,row); print(v,t); }
