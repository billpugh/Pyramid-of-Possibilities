//
//  FlashEcho.h
//
//  Created by Danny on 8/10/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __FlashEcho__
#define __FlashEcho__

#include "RNAnimation.h"
#include <string.h>
#include "RNGradient.h"


const uint16_t historySize = 64;
const uint8_t kDefaultMinBrightness = 5;

struct FlashEchoParameters {
    uint16_t lullDuration = 2000; // time (in ms) before we switch from RED to GREEN mode
    uint8_t minBrightness = kDefaultMinBrightness;
    uint8_t maxBrightness = 255;
    uint8_t fadeFactor = 10;
    float minActivityThreshold = 0.1;
    float maxActivityThreshold = 1;
    RNGradient recordingGradient = RNGradient(0, RNGradientWrap, 0xff0000, 0xff0000);
    RNGradient playbackGradient = RNGradient(0, RNGradientWrap, 0x00ff00, 0x0000ff);
};


class FlashEcho : public RNAnimation {
public:
    FlashEcho(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis, sizeof(FlashEchoParameters), &parameters) {
    	// initalize the buffer to zero
    	brightness = kDefaultMinBrightness;
    	replayMode = false;
        lastModeSwitchTimestamp = 0;
        recordingDuration = 0;
        loopCount = 0;
        tapEligible = true;
        lastTapTimestamp = 0;
    	clearHistory();
    };

    virtual void paint(RNLights & lights);
    virtual const char * name();

    void flash();
    void recordFlash();
    void fade();
    void clearHistory();
    void playHistory();
    void setIsReplaying(bool replaying);

    FlashEchoParameters parameters;

    int brightness;
    bool replayMode;
    bool tapEligible;

    unsigned long lastModeSwitchTimestamp;
    unsigned long tapHistory[historySize];
    unsigned long recordingDuration;
    unsigned long loopCount;
    unsigned long lastTapTimestamp;
    int historyWriteHead;
    int historyReadHead;

};

#endif /* defined(__FlashEcho__) */
