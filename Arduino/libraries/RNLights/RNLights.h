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
    // Specify the number of pixels assocaited with this set of RNLights
    RNLights(uint16_t numPixels);
    ~RNLights();
    
    // Set overall brightness (non-destructive), 256 = max
    void setBrightness(uint16_t amount=256);
    // Get overall brightness
    uint16_t getBrightness();
    
    
    // Get number of pixels
    uint16_t getNumPixels();
    // wrap pixel address (e.g., -1 -> getNumPixels()-1
    uint16_t normalize(int16_t pixel);
    // reset colors to black set brightness to full
    void reset();
    // copy pixel colors
    void copyPixels(RNLights & from);
    // set pixel colors using maximum of current or from colors
    void copyPixelsMax(RNLights & from);
    // rotate pixel values
    void rotate(bool up);
    // shift pixel values, filling in with black
    void shift(bool up);
    
    // Various methods for getting/setting pixel color
    void setPixelColor(uint16_t pixel, uint32_t colorRGB);
    void setPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
    void blendPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
    void setPixelHSV(uint16_t pixel, uint8_t hue, uint8_t saturation, uint8_t value);
    void blendPixelHSV(uint16_t pixel, uint8_t hue, uint8_t saturation, uint8_t value);
    
    void setPixelColorMax(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
    //  void setPixelColorMax(uint16_t pixel, uint32_t colorRGB);
    void addPixelColor(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue);
    void copyPixelColor(uint16_t fromPixel, uint16_t toPixel);
    
    void getPixelColor(uint16_t pixel, uint8_t &red, uint8_t &green, uint8_t &blue);
    
    uint8_t getPixelRed(uint16_t pixel);
    uint8_t getPixelGreen(uint16_t pixel);
    uint8_t getPixelBlue(uint16_t pixel);
    uint32_t getPixelColor(uint16_t pixel);
    
    // Set all pixels to the same color
    void setAllPixelColors(uint8_t red, uint8_t green, uint8_t blue);
    void setAllPixelColors(uint32_t colorRGB);
    void setAllPixelColorsMax(uint8_t red, uint8_t green, uint8_t blue);
    void setAllPixelColorsMax(uint32_t colorRGB);
    
    void setAllPixelHSVs(uint8_t hue, uint8_t saturation, uint8_t value);
    
    // Apply brightness values to individual pixels and set strip brightness to full brightness
    // useful when merging two strips that may have different brightness levels set.
    void applyBrightness();
    
    // Gets the average pixel brightness (ignoring overall brightness)
    uint8_t getAvgPixelBrightness();
    
    // Set the fade parameters; ms is current time
    void setFade(long unsigned ms, uint16_t halfLifeMS);
    // Set the linear fade parameters; ms is current time
    void setLinearFade(long unsigned ms, uint8_t fadePerSec);
    // update the fade; ms is current time
    int fade(unsigned long ms);
    
    virtual unsigned long show();
    
    
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

