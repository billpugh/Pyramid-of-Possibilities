//
//  RNLights.h
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#ifndef __RNLights__
#define __RNLights__

#include <stdint.h>

class RNLights {

public:
  RNLights(uint16_t numPixels);
  ~RNLights();

  void setBrightness(uint16_t amount=256);
  uint16_t getBrightness();

  void setFade(long unsigned ms, uint8_t fadePerSec, bool linearFade=true);
  uint16_t getNumPixels();
  uint16_t normalize(int16_t pixel);
  void reset();
  void copyPixels(RNLights & from);
  void copyPixelsMax(RNLights & from);
  void rotate(bool up);
  void shift(bool up);
  int fade(unsigned long ms);
  void setPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
  void setPixelHSV(uint16_t pixel, uint8_t hue, uint8_t saturation, uint8_t value);
  
  void setPixelColorMax(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
  void addPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
  void setAllPixelColors(uint8_t red, uint8_t green, uint8_t blue);
  void setAllPixelHSVs(uint8_t hue, uint8_t saturation, uint8_t value);
  
  void getPixelColor(uint16_t pixel, uint8_t &red, uint8_t &green, uint8_t &blue);
  void copyPixelColor(uint16_t fromPixel, uint16_t toPixel);

  uint8_t getPixelRed(uint16_t pixel);
  uint8_t getPixelGreen(uint16_t pixel);
  uint8_t getPixelBlue(uint16_t pixel);

protected:
  void fade(uint8_t amount, uint8_t minimum);
  void fadeMultiply(uint8_t amount, uint8_t minimum);
  const uint16_t numPixels;
  uint16_t offset;
  bool fullBrightness;
  uint8_t brightness;
  unsigned long lastFade;
  uint8_t fadePerSec;
  double logFade;
  bool linearFade;
  
  

  // Note: pixel i is stored at pixel[(i+offset) % numPixels];
  uint8_t * pixels;
  uint8_t * pixelsEnd;
};

#endif /* defined(__RNLights__) */

