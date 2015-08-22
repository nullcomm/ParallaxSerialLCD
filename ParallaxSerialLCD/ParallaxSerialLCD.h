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

#ifndef ParallaxSerialLCD_h
#define ParallaxSerialLCD_h

#include <Arduino.h>

class ParallaxSerialLCD : public SoftwareSerial {
public:
   ParallaxSerialLCD ( int pin, int numRows, int numCols );
   void setup ( boolean startEmpty=true );

   void display();
   void noDisplay();
   void clear();
   void setCursor(uint8_t col, uint8_t row);

   void lf ();
   void cr ();

   void scrollDisplayLeft ();
   void scrollDisplayRight ();

   void backlight (); //Backlight only available with model numbers 27977, 27979
   void noBacklight (); //Backlight only available with model numbers 27977, 27979

   void blink();
   void noBlink();
   void cursor();
   void noCursor ();

   void cursorOnChrBlink();

   // Make music
   void playTone ( int duration, int scale, int note );

   // Custom characters
   void createChar(int charIndex, unsigned char bytes[]);
   void printCustomChar(int charIndex);

	// shortcuts for printing at particular positions
   void at ( int row, int col, char );
   void at ( int row, int col, const char[] );
   void at ( int row, int col, String );
   void at ( int row, int col, uint8_t );
   void at ( int row, int col, int );
   void at ( int row, int col, unsigned int );
   void at ( int row, int col, long );
   void at ( int row, int col, unsigned long );
   void at ( int row, int col, long, int );

private:
	int _bv[9];
};


#endif
