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


const uint8_t kDefaultMinBrightness = 5;
const uint8_t kDefaultMaxBrightness = 255;
const uint16_t historySize = 64;
const unsigned long kDefaultLullDuration = 2000;   // in ms


struct FlashEchoParameters {
    unsigned long lullDuration; // time (in ms) before we switch from RED to GREEN mode
    uint8_t minBrightness;
    uint8_t maxBrightness;
    uint8_t fadeFactor;
};


class FlashEcho : public RNAnimation {
public:
    FlashEcho(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis, sizeof(FlashEchoParameters), &parameters) {
    	// initalize the buffer to zero
    	brightness = kDefaultMinBrightness;
    	replayMode = 1;
        lastModeSwitchTimestamp = 0;
        recordingDuration = 0;
        loopCount = 0;
    	clearHistory();

        parameters.lullDuration = kDefaultLullDuration;
        parameters.minBrightness = kDefaultMinBrightness;
        parameters.maxBrightness = kDefaultMaxBrightness;
        parameters.fadeFactor = 10;
    };

    virtual void paint(RNLights & lights);
    virtual const char * name();

    FlashEchoParameters parameters;

    void flash();
    void recordFlash();
    void fade();
    void clearHistory();
    void playHistory();
    void setIsReplaying(int replaying);

    int brightness;
    int replayMode;

    unsigned long tapHistory[historySize];
    unsigned long recordingDuration;
    unsigned long loopCount;
    int historyWriteHead;
    int historyReadHead;

    unsigned long lastModeSwitchTimestamp;
};

#endif /* defined(__FlashEcho__) */
