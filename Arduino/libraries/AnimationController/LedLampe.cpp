#include "LedLampe.h"

/** set a pixel of the lamp (0-85, counted from top). No Delay or paint
 * f_pixel_num: the number of pixel to set. two pixels will be set (front&back)
 */
void LedLampe::setPixelColor(uint16_t f_pixel_num, uint8_t r, uint8_t g, uint8_t b)
{
  if( f_pixel_num>_sizeOnEachSide)
    return;
	
  uint16_t p1 = _center-f_pixel_num;
  uint16_t p2 = _center+f_pixel_num;
  
  Adafruit_NeoPixel::setPixelColor(p1, Adafruit_NeoPixel::Color( r, g, b));
  Adafruit_NeoPixel::setPixelColor(p2, Adafruit_NeoPixel::Color( r, g, b));
}

/** set a pixel of the lamp (0-85, counted from top). No Delay or paint
 * f_pixel_num: the number of pixel to set. two pixels will be set (front&back)
 */
void LedLampe::setPixelColor(uint16_t f_pixel_num, uint32_t c)
{
  if( f_pixel_num>_sizeOnEachSide)
    return;
	
  uint16_t p1 = _center-f_pixel_num;
  uint16_t p2 = _center+f_pixel_num;
  
  Adafruit_NeoPixel::setPixelColor(p1, c);
  Adafruit_NeoPixel::setPixelColor(p2, c);
}

uint16_t LedLampe::numPixels(void) const {
  return _sizeOnEachSide+1;
}

uint32_t LedLampe::ColorHSV(float h, float s, float v)
{
  //https://gist.github.com/hdznrrd/656996
  int i;
  float f,p,q,t;
  byte r,g,b;
  
  h = max(0.0, min(360.0, h));
  s = max(0.0, min(100.0, s));
  v = max(0.0, min(100.0, v));
  
  s /= 100;
  v /= 100;
  
  if(s == 0) {
    // Achromatic (grey)
    r = g = b = round(v*255);
    return Adafruit_NeoPixel::Color( r,  g,  b);
  }
 
  h /= 60; // sector 0 to 5
  i = floor(h);
  f = h - i; // factorial part of h
  p = v * (1 - s);
  q = v * (1 - s * f);
  t = v * (1 - s * (1 - f));
  switch(i) {
    case 0:
      r = round(255*v);
      g = round(255*t);
      b = round(255*p);
      break;
    case 1:
      r = round(255*q);
      g = round(255*v);
      b = round(255*p);
      break;
    case 2:
      r = round(255*p);
      g = round(255*v);
      b = round(255*t);
      break;
    case 3:
      r = round(255*p);
      g = round(255*q);
      b = round(255*v);
      break;
    case 4:
      r = round(255*t);
      g = round(255*p);
      b = round(255*v);
      break;
    default: // case 5:
      r = round(255*v);
      g = round(255*p);
      b = round(255*q);
    }
	// check that no value is 255
  return Adafruit_NeoPixel::Color( r,  g,  b);
}

void LedLampe::setAllPixelColor(uint32_t c)
{
  for( uint16_t i=0; i<Adafruit_NeoPixel::numPixels(); i++)
  {
	Adafruit_NeoPixel::setPixelColor(i, c);
  }
}

void LedLampe::setAllPixelColor(uint8_t r, uint8_t g, uint8_t b)
{
  setAllPixelColor( Adafruit_NeoPixel::Color(r, g, b));
}

uint32_t LedLampe::ColorAdafruit(byte WheelPos) 
{
  if(WheelPos < 85) {
   return Adafruit_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return Adafruit_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

void LedLampe::setNPixelColor( uint16_t pixelNumberInStrip, uint8_t numOfPixels, uint32_t color)
{
  if( pixelNumberInStrip>_sizeOnEachSide)
    return;

  setPixelColor( pixelNumberInStrip, color);
  for( int i=0; i<numOfPixels; i++ )
  {
    // int pixel_adder=i;
    // if( i%2 != 0 )
	  // pixel_adder*= (-1);
	setPixelColor(pixelNumberInStrip+i, color);
  }
  
}
