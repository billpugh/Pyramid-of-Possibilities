//
//  RNLights.cpp
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#include "RNLights.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "hsv2rgb.h"

RNLights::RNLights(uint16_t numPixels) : 
numPixels(numPixels) {
  size_t sz = numPixels * 3; 
  pixels = (uint8_t*)malloc(sz);
  pixelsEnd = pixels + sz;
  reset();
}

RNLights::~RNLights() {
  free(pixels);
}

void RNLights::reset() {
  fullBrightness = true;
  brightness = 0;
  for(int i = 0; i < numPixels*3; i++)
    pixels[i] = 0;
  offset = 0;
}
void RNLights::applyBrightness() {
  if (fullBrightness) return;
  fullBrightness = true;
  uint8_t br = brightness;
  for(int i = 0; i < numPixels*3; i++) {
     uint16_t value = pixels[i];
     pixels[i] =  ( br * value ) >> 8;
     }
  brightness = 0;
}

void RNLights::setLinearFade(long unsigned ms, uint8_t fadePerSec) {
  this->lastFade = ms;
  this->fadePerSec = fadePerSec;
  this->linearFade = true;
}
void RNLights::setFade(long unsigned ms, uint16_t halfLifeMS) {
  this->lastFade = ms;
  this->linearFade = false;
  logFade = -693.1471806; // 1000*log(1/2);
  logFade = logFade / halfLifeMS;
}


int RNLights::fade(unsigned long ms) {
  unsigned long since = ms - lastFade;
  if (since > 1000)
    since = 1000;
  if (linearFade) {
    uint8_t amount = ((uint32_t)fadePerSec) * since / 1000;
    if (amount < 1)
      return 0;
    lastFade = ms;
    fade(amount, 0);
    return amount;
  } else {
    double v = logFade * since / 1000;
    if (v > -0.04) {
      // not enough time passed to do a significant fade
      return 256;
    }
    int fadeAmount = exp(v) * 256;
    fadeMultiply(fadeAmount, 0);
    lastFade = ms;
    return fadeAmount;
  }
}

uint8_t RNLights::getAvgPixelBrightness() {
  uint32_t total = 0;
  for(int i = 0; i < numPixels*3; i++) {
    uint8_t v = pixels[i];
    total += v;
    }
  total = total / (numPixels*3);
  if (total > 255)
    return 255;
  return total;
}

void RNLights::fade(uint8_t amount, uint8_t minimum) {

  for(int i = 0; i < numPixels*3; i++) {
    uint8_t v = pixels[i];
    if (v <= minimum) continue;
    if (v <= minimum + amount)
      pixels[i] = minimum;
    else 
      pixels[i] = v-amount;
  }
}

void RNLights::fadeMultiply(uint8_t amount, uint8_t minimum) {

  for(int i = 0; i < numPixels*3; i++) {
    uint8_t v = pixels[i];
    if (v <= minimum) continue;
    uint16_t v16 = v;
    v = (v16 * amount) >> 8;
    if (v <= minimum) 
      pixels[i] = minimum;
    else 
      pixels[i] = v;
  }
}

void RNLights::copyPixelsMax(RNLights & from) {
  uint8_t r,g,b;

  for(int i = 0; i < numPixels; i++) {
    from.getPixelColor(i, r, g, b);
    setPixelColorMax(i, r, g, b);
  }
}

void RNLights::copyPixels(RNLights & from) {
  uint8_t r,g,b;

  for(int i = 0; i < numPixels; i++) {
    from.getPixelColor(i, r, g, b);
    setPixelColor(i, r, g, b);
  }
  //  uint8_t * fromP = &from.pixels[from.offset];
  //  uint8_t * toP = &pixels[offset];
  //  for(uint16_t i = 0; i < numPixels; i++) {
  //    *toP++ = *fromP++;
  //    *toP++ = *fromP++;
  //    *toP++ = *fromP++;
  //    if (toP >= pixelsEnd)
  //      toP = pixels;
  //    if (fromP >= from.pixelsEnd)
  //      fromP = from.pixels;
  //  }
}



void RNLights::rotate(bool up) {
  // if up, what was v[i] should now be at v[i+1]
  if (up) {
    if (offset == 0)
      offset = numPixels-1;
    else offset--;
  } 
  else  if (offset == numPixels-1)
    offset = 0;
  else
    offset++;
}
void RNLights::shift(bool up) {
  rotate(up);
  if (up)
    setPixelColor(0, 0, 0, 0);
  else
    setPixelColor(numPixels-1, 0, 0, 0);
}


void RNLights::setPixelColor(uint16_t pixel, uint32_t colorRGB) {
  pixel = 3*((pixel+offset) % numPixels);
  pixels[pixel] = (uint8_t) (colorRGB >> 16);
  pixels[pixel+1] = (uint8_t) (colorRGB >> 8);
  pixels[pixel+2] = (uint8_t) colorRGB;
}

//void RNLights::setPixelColorMax(uint16_t pixel, uint32_t colorRGB) {
//    setPixelColorMax(pixel,
//        (colorRGB >> 16), (colorRGB >> 8),  colorRGB);
//}

uint32_t RNLights::getPixelColor(uint16_t pixel) {
  pixel = 3*((pixel+offset) % numPixels);
  return (pixels[pixel] << 16)
	| (pixels[pixel+1] << 8)
	| (pixels[pixel+2]);
}

void RNLights::setPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue) {
  pixel = 3*((pixel+offset) % numPixels);
  pixels[pixel] = red;
  pixels[pixel+1] = green;
  pixels[pixel+2] = blue;
}

void RNLights::blendPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue) {
  pixel = 3*((pixel+offset) % numPixels);
  pixels[pixel] = (pixels[pixel] + (uint16_t) red)/2;
  pixels[pixel+1] = (pixels[pixel+1] + (uint16_t) green)/2;
  pixels[pixel+2] = (pixels[pixel+2] + (uint16_t) blue)/2;
}

void RNLights::setPixelHSV(uint16_t pixel, uint8_t hue, uint8_t saturation, uint8_t value) {
  CHSV hsv;
  CRGB rgb;
  hsv.h = hue;
  hsv.s = saturation;
  hsv.v = value;
  hsv2rgb_rainbow(hsv,rgb);
  setPixelColor(pixel, rgb.r, rgb.g, rgb.b);
}
void RNLights::blendPixelHSV(uint16_t pixel, uint8_t hue, uint8_t saturation, uint8_t value) {
  CHSV hsv;
  CRGB rgb;
  hsv.h = hue;
  hsv.s = saturation;
  hsv.v = value;
  hsv2rgb_rainbow(hsv,rgb);
  blendPixelColor(pixel, rgb.r, rgb.g, rgb.b);
}



inline void setMax(uint8_t & current, uint8_t value) {
  if (current < value)
    current = value;
}
void RNLights::setPixelColorMax(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue) {
  pixel = 3*((pixel+offset) % numPixels);
  setMax(pixels[pixel], red);
  setMax(pixels[pixel+1], green);
  setMax(pixels[pixel+2], blue);
}
inline void addByte(uint8_t & current, uint8_t value) {
  uint16_t sum = current + value;
  if (sum < 255)
    current = sum;
  else
    current = 255;
}
void RNLights::addPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue) {
  pixel = 3*((pixel+offset) % numPixels);
  addByte(pixels[pixel], red);
  addByte(pixels[pixel+1], green);
  addByte(pixels[pixel+2], blue);
}

void RNLights::setAllPixelHSVs( uint8_t hue, uint8_t saturation, uint8_t value) {
  CHSV hsv;
  CRGB rgb;
  hsv.h = hue;
  hsv.s = saturation;
  hsv.v = value;
  hsv2rgb_rainbow(hsv,rgb);
  setAllPixelColors(rgb.r, rgb.g, rgb.b);
}

void RNLights::setAllPixelColors(uint8_t red, uint8_t green, uint8_t blue) {
  uint8_t *p = pixels;
  uint8_t * pixelsEnd = p + numPixels*3;
  while(p < pixelsEnd) {
    *p++ = red;
    *p++ = green;
    *p++ = blue;
  }
}
void RNLights::setAllPixelColorsMax(uint8_t red, uint8_t green, uint8_t blue) {
    uint8_t *p = pixels;
    uint8_t * pixelsEnd = p + numPixels*3;
    while(p < pixelsEnd) {
        setMax(*p++, red);
        setMax(*p++, green);
        setMax(*p++, blue);
    }
}

void RNLights::setAllPixelColors(uint32_t colorRGB) {
    setAllPixelColors((uint8_t) (colorRGB >> 16),
                         
                         (uint8_t) (colorRGB >> 8),
                         (uint8_t) colorRGB);
}

void RNLights::setAllPixelColorsMax(uint32_t colorRGB) {
    setAllPixelColorsMax((uint8_t) (colorRGB >> 16),

                      (uint8_t) (colorRGB >> 8),
                      (uint8_t) colorRGB);
}

void RNLights::getPixelColor(uint16_t pixel, uint8_t &red, uint8_t &green, uint8_t &blue) {
  pixel = 3*((pixel+offset) % numPixels);
  red = pixels[pixel];
  green = pixels[pixel+1];
  blue = pixels[pixel+2];
}

void RNLights::copyPixelColor(uint16_t fromPixel, uint16_t toPixel) {
  fromPixel = 3*((fromPixel+offset) % numPixels);
  toPixel = 3*((toPixel+offset) % numPixels);
  pixels[toPixel++] = pixels[fromPixel++];
  pixels[toPixel++] = pixels[fromPixel++];
  pixels[toPixel] = pixels[fromPixel];
}

uint8_t RNLights::getPixelRed(uint16_t pixel) {
  pixel = 3*((pixel+offset) % numPixels);
  return pixels[pixel];
}
uint8_t RNLights::getPixelGreen(uint16_t pixel)  {
  pixel = 3*((pixel+offset) % numPixels);
  return pixels[pixel+1];
}

uint8_t RNLights::getPixelBlue(uint16_t pixel)  {
  pixel = 3*((pixel+offset) % numPixels);
  return pixels[pixel+2];
}

void RNLights::setBrightness(uint16_t amount) {
  if(amount == 256)
    fullBrightness = true;
  else {
    fullBrightness = false;
    brightness = (uint8_t) amount;
  }
}
uint16_t RNLights::getBrightness() {
  if (fullBrightness)
    return 256;
  return brightness;
}

uint16_t RNLights::normalize(int16_t pixel) {
  while (pixel < 0)
    pixel += numPixels;
  if (pixel < numPixels)
    return pixel;
  return pixel % numPixels;
}

uint16_t RNLights::getNumPixels() {
  return numPixels;
}


unsigned long RNLights::show() {
	return 0;
	}







