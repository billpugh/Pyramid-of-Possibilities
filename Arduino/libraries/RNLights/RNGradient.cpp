//
//  RNGradient.cpp
//  PlatformData
//
//  Created by Bill on 7/31/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "RNGradient.h"
#include "hsv2rgb.h"


RNGradient::RNGradient(bool isHSV,
                       RNGradientKind kind,
                       uint16_t s1,
                       uint8_t s2, uint8_t  s3,
                       uint16_t e1,
                       uint8_t e2, uint8_t  e3) :
isHSV(isHSV), kind(kind), s1(s1), s2(s2), s3(s3),
e1(e1), e2(e2), e3(e3) {
}

RNGradient::RNGradient(bool isHSV,
                       RNGradientKind kind,
                       uint32_t startValue,
                       uint32_t endValue) : isHSV(isHSV), kind(kind), s1(startValue>>16), s2(startValue>>8), s3(startValue),
e1(endValue>>16), e2(endValue>>8), e3(endValue) {}

uint8_t RNGradient::normalize(int32_t position) {
    switch (kind) {
        default:
        case RNGradientWrap:
            return (uint8_t) position;
        case RNGradientBounce:
            position = position & 0x1ff;
            if (position > 255)
                position = 511-position;
            return position;
        case RNGradientCapped:
            if (position < 0) return 0;
            if (position > 255) return 255;
            return position;
    }
    
}

inline  uint8_t RNGradient::mix(uint8_t position, uint8_t s, uint8_t e) {
    return ((256-position)*s + position * e)/255;
}
inline  uint16_t RNGradient::mix(uint8_t position, uint16_t s, uint16_t e) {
    return ((256-position)*s + position * e)/255;
}
inline void RNGradient::getValue(int32_t position, uint8_t &v1, uint8_t &v2, uint8_t &v3) {
    position = normalize(position);
    v1 = mix(position, s1, e1);
    v2 = mix(position, s2, e3);
    v3 = mix(position, s3, e3);
}
void RNGradient::getColor(int32_t position, uint8_t &red, uint8_t &green, uint8_t &blue) {
    uint8_t v1, v2, v3;
    getValue(position, v1, v2, v3);
    if (isHSV) {
        CHSV hsv;
        CRGB rgb;
        hsv.h = v1;
        hsv.s = v2;
        hsv.v = v3;
        hsv2rgb_rainbow(hsv,rgb);
        red = rgb.r;
        green = rgb.g;
        blue = rgb.b;
    } else {
        red = v1;
        green = v2;
        blue = v3;
    }
}


uint32_t RNGradient::getColor(int32_t position) {
    uint8_t r, g, b;
    getColor(position, r, g, b);
    return (r << 16) | (g << 8) | b;
}

uint32_t RNGradient::getValue(int32_t position) {
    uint8_t v1, v2, v3;
    getValue(position, v1, v2, v3);
    return (v1 << 16) | (v2 << 8) | v3;
}

