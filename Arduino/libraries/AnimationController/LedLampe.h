// led lampe

#ifndef LedLampe_h
#define LedLampe_h

#include <Adafruit_NeoPixel.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_NeoMatrix.h>


#define COL_BLACK_32    0x000000
#define COL_RED_32      0xFF0000
#define COL_GREEN_32    0x00FF00
#define COL_BLUE_32     0x0000FF
#define STRIPE_CENTER_8 60
#define LAMP_LENGTH     60 

//Adafruit_NeoPixel matrix  = Adafruit_NeoPixel(121, 6, NEO_GRB + NEO_KHZ800);

class LedLampe : public Adafruit_NeoPixel
{
	public:
	  LedLampe(uint16_t n, uint8_t p=6, uint8_t t=NEO_GRB + NEO_KHZ800)
	    :Adafruit_NeoPixel( n, p, t)
		{
			_center = 60;
			_sizeOnEachSide = 60;
		};
	  void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
      void setPixelColor(uint16_t n, uint32_t c);
	  uint16_t numPixels(void) const;
	  void setAllPixelColor(uint32_t c);
	  void setAllPixelColor(uint8_t r, uint8_t g, uint8_t b);
	  void setNPixelColor( uint16_t pixelNum, uint8_t numOfPixels, uint32_t color);
	  static uint32_t ColorHSV(float h, float s, float v);
	  static uint32_t ColorAdafruit(byte WheelPos); 
	private:
	  uint16_t _center;
	  uint16_t _sizeOnEachSide;
};

#endif
