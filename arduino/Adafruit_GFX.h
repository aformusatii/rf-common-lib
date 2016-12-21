/******************************************************************
 This is the core graphics library for all our displays, providing
 basic graphics primitives (points, lines, circles, etc.). It needs
 to be paired with a hardware-specific library for each display
 device we carry (handling the lower-level functions).
 
 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source hardware
 by purchasing products from Adafruit!
 
 Written by Limor Fried/Ladyada for Adafruit Industries.
 Processing-like API written by Enrico Gueli for Officine Arduino.
 BSD license, check license.txt for more information.
 All text above must be included in any redistribution.
 ******************************************************************/

#ifndef _ADAFRUIT_GFX_H
#define _ADAFRUIT_GFX_H

#include "Print.h"

/*
 * This library can work with or without the presence of an SD
 * reading library (to load images). At the moment, only the
 * Arduino SD library is supported; it is included in
 * standard Arduino libraries.
 * 
 * The presence of the SD library is detected by looking at the
 * __SD_H__ preprocessor variable, defined into 
 * Arduino SD library to avoid double inclusion. This means
 * that in order to use the image-related API of Adafruit_GFX,
 * SD.h *must* be included before Adafruit_GFX.
 * 
 * The bottom part of this include file contains the actual image
 * loading code; if it was in a separate .cpp file, there were no
 * way to check if the SD library was present or not.
 * 
 * A partial solution was to include SD.h anyway, see if that works
 * (i.e. it is found in the include search path) and act accordingly.
 * But this solution relied on the preprocessor to issue only a
 * warning when an include file is not found. Avr-gcc, used for
 * Arduino 8-bit MCUs, does that, but the standard gcc-4.4, used for
 * Arduino Due, issues a fatal error and stops compilation.
 * 
 * The best solution so far is to put the code here. It works if this
 * include is used only in one .cpp file in the build (this is the
 * case of most Arduino sketches); if used in multiple .cpp files,
 * the linker may complain about duplicate definitions.
 * 
 */

#define swap(a, b) { int16_t t = a; a = b; b = t; }

/* TODO
enum RectMode {
  CORNER,
  CORNERS,
  RADIUS,
  CENTER
};
*/

typedef uint16_t color;

class Adafruit_GFX : public Print {
 public:

  Adafruit_GFX(int16_t w, int16_t h); // Constructor
  virtual ~Adafruit_GFX() {}

  // This MUST be defined by the subclass
  virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;

  

  // These MAY be overridden by the subclass to provide device-specific
  // optimized code.  Otherwise 'generic' versions are used.
  virtual void 
	drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, 
		uint16_t color),
  	drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color),
	drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color),
	drawRect(int16_t x, int16_t y, int16_t w, int16_t h, 
		uint16_t color),
	fillRect(int16_t x, int16_t y, int16_t w, int16_t h, 
		uint16_t color),
	fillScreen(uint16_t color),
	invertDisplay(bool i);

// These exist only with Adafruit_GFX (no subclass overrides)
  void
	drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),
	drawCircleHelper(int16_t x0, int16_t y0,
			int16_t r, uint8_t cornername, uint16_t color),
	fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color),
	fillCircleHelper(int16_t x0, int16_t y0, int16_t r,
		      uint8_t cornername, int16_t delta, uint16_t color),

	drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		    int16_t x2, int16_t y2, uint16_t color),
	fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		    int16_t x2, int16_t y2, uint16_t color),
	drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
		     int16_t radius, uint16_t color),
	fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h,
		     int16_t radius, uint16_t color),

	drawBitmap(int16_t x, int16_t y, 
		  const uint8_t *bitmap, int16_t w, int16_t h,
		  uint16_t color),
	drawChar(int16_t x, int16_t y, unsigned char c,
		uint16_t color, uint16_t bg, uint8_t size),
	setCursor(int16_t x, int16_t y),
	setTextColor(uint16_t c),
	setTextColor(uint16_t c, uint16_t bg),
	setTextSize(uint8_t s),
	setTextWrap(bool w),
	setRotation(uint8_t r);

  virtual size_t write(uint8_t);

  int16_t 
	height(void),
	width(void);


  uint8_t getRotation(void);

  
  /*
   * Processing-like graphics primitives
   */
  
  /// transforms a color in 16-bit form given the RGB components.
  /// The default implementation makes a 5-bit red, a 6-bit
  /// green and a 5-bit blue (MSB to LSB). Devices that use
  /// different scheme should override this. 
  virtual uint16_t newColor(uint8_t red, uint8_t green, uint8_t blue);
  
  
  void
	// http://processing.org/reference/background_.html
	background(uint8_t red, uint8_t green, uint8_t blue),
	background(color c),

	// http://processing.org/reference/fill_.html
	fill(uint8_t red, uint8_t green, uint8_t blue),
	fill(color c),

	// http://processing.org/reference/noFill_.html
	noFill(),

	// http://processing.org/reference/stroke_.html
	stroke(uint8_t red, uint8_t green, uint8_t blue),
	stroke(color c),

	// http://processing.org/reference/noStroke_.html
	noStroke(),
  
	text(const char * text, int16_t x, int16_t y),
	textWrap(const char * text, int16_t x, int16_t y),

	textSize(uint8_t size),
  
	// similar to ellipse() in Processing, but with
	// a single radius.
	// http://processing.org/reference/ellipse_.html
	circle(int16_t x, int16_t y, int16_t r),
	point(int16_t x, int16_t y),
	line(int16_t x1, int16_t y1, int16_t x2, int16_t y2),
	quad(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3, int16_t x4, int16_t y4),
rect(int16_t x, int16_t y, int16_t width, int16_t height),
	rect(int16_t x, int16_t y, int16_t width, int16_t height, int16_t radius),
	triangle(int16_t x1, int16_t y1, int16_t x2, int16_t y2, int16_t x3, int16_t y3);
  
  /* TODO
  void rectMode(RectMode mode);
  
  void pushStyle();
  void popStyle();
  */
  
 protected:
  int16_t
	WIDTH, HEIGHT;   // this is the 'raw' display w/h - never changes
  int16_t
	_width, _height, // dependent on rotation
	cursor_x, cursor_y;
  uint16_t
	textcolor, textbgcolor;
  uint8_t
	textsize,
	rotation;
  bool
	wrap; // If set, 'wrap' text at right edge of display
  
  /*
   * Processing-style graphics state
   */
  
  color strokeColor;
  bool useStroke;
  color fillColor;
  bool useFill;
};

#endif // _ADAFRUIT_GFX_H