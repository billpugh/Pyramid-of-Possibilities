//
//  RNDigit.cpp
//  PachinkoTestbed
//
//  Created by Bill on 4/20/15.
//
//

#include "RNDigit.h"

#include "OctoWS2811.h"


int delayval = 500; // delay for half a second

int digitPixels[10][41] = {// 0
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    // 1
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // 2
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1},
    // 3
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1},
    // 4
    {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    // 5
    {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    // 6
    {1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    // 7
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    // 8
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1},
    // 9
    {1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}};


RNDigit::RNDigit(OctoWS2811 & lights, int firstPixel) : lights(lights), firstPixel(firstPixel) , skipPixels(0), numPixels(MAX_PIXELS) {
    rgb = 0x008000;
}

RNDigit::RNDigit(OctoWS2811 & lights, int firstPixel, int skipPixels, int numPixels) : lights(lights), firstPixel(firstPixel), skipPixels(skipPixels), numPixels(numPixels) {
    rgb = 0x008000;
}

void RNDigit::setPixel(int pixel, int rgb) {
    lights.setPixel(firstPixel+(pixel%numPixels), rgb);
}
void RNDigit::setColor(int rgb) {
    this->rgb = rgb;
}

int RNDigit::nextPixel() {
    return firstPixel+numPixels;
}

void RNDigit::clear() {
    for(int i = 0; i < numPixels; i++)
        lights.setPixel(firstPixel+i, 0);
}

void RNDigit::test(int rgb) {
    for(int i = 0; i < numPixels; i++)
        lights.setPixel(firstPixel+i, rgb);
}

void RNDigit:: setDigit(int d) {
    for(int i = 0; i < numPixels; i++)
        if (digitPixels[d][i+skipPixels])
            lights.setPixel(firstPixel+i, rgb);
        else
            lights.setPixel(firstPixel+i, 0);
}


//void RNDigit::drawDigit(int d1, int rgb1, int d2, int rgb2) {
//    for(int i = firstPixel; i < firstPixel+numPixels; i++) {
//        int c1 = 0;
//        if (d1 >= 0 && digitPixels[d1][i])
//            c1 = 1;
//        int c2 = 0;
//        if (d2 >= 0 && digitPixels[d2][i])
//            c2 = 1;
//        lights->setPixelColor(i, (c1*rgb1+c2*rgb2))>> 8;
//    }
//}


