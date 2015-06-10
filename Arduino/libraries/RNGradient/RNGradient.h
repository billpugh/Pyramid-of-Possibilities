//
//  RNGradient.h
//
//  Created by Bill on 7/31/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __RNGradient__
#define __RNGradient__

#include <stdint.h>

enum  RNGradientKind {
    RNGradientWrap,  RNGradientBounce,  RNGradientCapped
};


// A gradient provides a way blending from one color to another.
// A gradient can either be a HSV or a RGB gradiant
// When getting a color from a gradient, you give a position.
//  a position of 0 gives you the starting color, a position of 255 gives you the ending color.
// The values returned by values outside that range depend on the kind of gradient.
//   * For a wrapped gradient, the gradient wraps around; position 256 is the same as 0.
//      Thus, the value go 0, 1, ..., 254, 255, 0, 1, ...
//   * For a bounce gradient, the gradient bounces back when it hits the end
//      The value go 0, 1, ..., 254, 255, 255, 254, 253, ..., 2, 1, 0, 0, 1, 2 ...
//   * For a capped gradient, the positions are capped at 0 and 255 (positions less than 0 are treated as 0,
//      positions greater than 255 are treated as 255).


// Note that the first value of the gradient is 16 bit. This is intended for HSV gradients, where you might want a 
class RNGradient {
public:
    RNGradient(bool isHSV,
               RNGradientKind kind,
               uint32_t startValue,
               uint32_t endValue);
    RNGradient(bool isHSV,
               RNGradientKind kind,
               uint16_t s1,
               uint8_t s2, uint8_t  s3,
               uint16_t e1,
               uint8_t e2, uint8_t  e3);
    
    void getValue(int32_t position, uint8_t &v1, uint8_t &v2, uint8_t &v3);
    void getColor(int32_t position, uint8_t &red, uint8_t &green, uint8_t &blue);
    uint32_t getColor(int32_t position);
    uint32_t getValue(int32_t position);
    const bool isHSV;
    const RNGradientKind kind;
    const uint16_t s1;
    const uint8_t s2, s3;
    const uint16_t e1;
    const uint8_t e2, e3;
    
private:

    uint8_t normalize(int32_t position);
    uint8_t mix(uint8_t position, uint8_t s, uint8_t e);
    uint16_t mix(uint8_t position, uint16_t s, uint16_t e);
    
};

#endif /* defined(__RNGradient__) */
