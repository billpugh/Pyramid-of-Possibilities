//
//  StripLighting.cpp
//
//  Created by Bill on 5/19/15.
//
//

#include "StripLighting.h"


StripLighting::StripLighting(OctoWS2811 & lights, int firstPixel, int numPixels) : lights(lights), firstPixel(firstPixel), numPixels(numPixels) {};



int randomColor() {
    CHSV hsv;
    hsv.h = random8();
    hsv.s = 40;
    hsv.v = 255;
    CRGB rgb;
    hsv2rgb_rainbow(hsv, rgb);
    return (rgb.r << 16 ) | (rgb.g << 8) | rgb.b;
    
}


void StripLighting::fill() {
    for(int i = 0; i < numPixels; i++)
        lights.setPixel(firstPixel+i, randomColor());
}

void StripLighting::rotate() {
    for(int i = 0; i < numPixels-1; i++)
        lights.setPixel(firstPixel+i, lights.getPixel(firstPixel+i+1));
    lights.setPixel(firstPixel+numPixels-1, randomColor());
}