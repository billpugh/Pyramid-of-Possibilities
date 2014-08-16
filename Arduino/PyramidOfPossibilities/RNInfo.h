//
//  RNInfo.h
//  PlatformData
//
//  Created by Bill on 7/17/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __RNInfo__
#define __RNInfo__

#include <stdint.h>
#include "Platform.h"
#include "RNLights.h"

class RNInfo : public Platform {
public:
    RNInfo(  uint8_t numLEDs, Platform & p);
    
    RNInfo(
           uint8_t numLEDs,
           uint8_t identifier,
           int16_t x,
           int16_t y,
           int16_t z);
    
    
    // Information about the platform
    // Number of visible LEDs on the platform
    const uint8_t numLEDs;
    // Get the global clock value (synchronized across all platforms)
    unsigned long getGlobalMillis();
    
    uint16_t getRandomPixel();
    int getRandom(int max);
    
    // Get the most recent reading from the accelerometer, combine all three axes.
    // Non-negative, passed through a high pass filter, will be 0.0 when everything is absolutely still.
    float getLocalActivity();
    // Get the individual x,y,z accelerometer readings passed through a high pass filter. Values may be negative.
    void getLocalXYZActivity(float data[3]);
    void getAndResetAccumulatedXYZActivity(float data[3]);

    // Get whether or not taps have been detected since the last paint refresh. If zero, no taps have been indicated.
    // This is a bit field, with different bits indicating whether the tap was in the X, Y or Z direction,
    // and whether it was positive or negative. In most cases, it is sufficient to check whether or not this value is nonzero.
    // Bits are:
    // AxX: 0x10 -- tap in X axis
    // PxX: 0x01 -- positive in X axis
    // AxY: 0x20 -- tap in Y axis
    // PxY: 0x02 -- positive in Y axis
    // AxZL 0x40 -- tap in Z axis
    // PxZ: 0x04 -- positive in Z axis
    uint8_t getTaps();
    uint8_t getAndResetAccumulatedTaps();

    // get the number of milliseconds since the last tap
    unsigned long timeSinceLastTap();
    
    // Get a combined indication of activity across all platforms. Same scale as getLocalActivity
    float getGlobalActivity();
    
    // getGlobalAngle for LED in degrees (0 = south, range = is 0 to 0.999...)
    float getGlobalAngle(uint8_t led);

    float getPlatformGlobalAngle();

    

    // getLocalAngle for LED in degrees (0 = south, range = is 0 to 0.999...)
    float getLocalAngle(uint8_t led);
    

    // getGlobalRadius for LED in mm (how far in the x/y plan is this LED from the center of the Pyramid
    float getGlobalRadius(uint8_t led);
    
    // Distance of pixel from center at ground level
    float getGlobalRadiusGround(uint8_t led);
    
    // does this LED face the exterior of the entire pyramid?
    bool isExteriorLED(uint8_t led);
    
    void showActivityWithSparkles(RNLights & lights);
    void showActivityWithBrightness(RNLights & lights,  uint16_t minBrightness);
    void showActivity(RNLights & lights, bool showSparkles, uint16_t minBrightness);
    
    void accelerometerCallback( float totalG,
                               float directionalG[3],
                               uint8_t source);

    // Call while doing any lengthy animations so we can do housekeeping.
    void yield();

    // print debugging information
    void println(const char *s);
    void printf(const char *fmt, ... );
    
private:
    float globalAngle[240];
    float globalRadius[240];
    float globalRadiusGround[240];
    float localAngle[240];
    
    float myTotalG;
    float platformGlobalAngle;
    float myDirectionalG[3];
    float maxDirectionalG[3];
    uint8_t myTapSource = 0;
    uint8_t accumulatedTaps;
    unsigned long lastTap;
    
    RNLights sparkles;
    
    void initialize();


    friend class RNController;
    // Call to update any internal structures before painting any animations
    // Only the controller should call this method
    void update();

};


#endif /* defined(__RNInfo__) */



