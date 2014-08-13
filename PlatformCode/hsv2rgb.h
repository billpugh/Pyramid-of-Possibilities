//
//  hsv2rgb.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef PlatformData_hsv2rgb_h
#define PlatformData_hsv2rgb_h


struct CRGB;
struct CHSV;

// Forward declaration of hsv2rgb_rainbow here,
// to avoid circular dependencies.
extern void hsv2rgb_rainbow( const CHSV& hsv, CRGB& rgb);

struct CHSV {
    union {
        struct {
            union {
                uint8_t hue;
                uint8_t h; };
            union {
                uint8_t saturation;
                uint8_t sat;
                uint8_t s; };
            union {
                uint8_t value;
                uint8_t val;
                uint8_t v; };
        };
        uint8_t raw[3];
    };
};

struct CRGB {
    union {
        struct {
            union {
                uint8_t r;
                uint8_t red;
            };
            union {
                uint8_t g;
                uint8_t green;
            };
            union {
                uint8_t b;
                uint8_t blue;
            };
        };
        uint8_t raw[3];
    };
    
};



#endif
