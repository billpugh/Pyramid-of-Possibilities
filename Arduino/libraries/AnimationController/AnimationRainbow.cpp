#include "AnimationRainbow.h"

// nothing to set up
void AnimationRainbow::setup()
{
}

// paint the whole frame in consecutive HSV colors
// @parameter frame will be a number from 0 until max(uint32_t).
void AnimationRainbow::paint( uint32_t frame )
{
   int j=frame;
   for(int i=0; i<_ledLampe.numPixels(); i++) 
	{
	  // the HSV color is a uint8_t so the uint32_t frame needs to be limited between 0 and 254 (the &255)
      _ledLampe.setPixelColor(i, LedLampe::ColorAdafruit((i+j) & 255));
    }
    _ledLampe.show();
}

// nothing to clean
void AnimationRainbow::cleanup()
{
}
