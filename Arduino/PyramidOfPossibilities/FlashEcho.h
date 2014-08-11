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


const uint8_t kMinBrightness = 5;
const uint16_t historySize = 5;


class FlashEcho : public RNAnimation {
public:
    FlashEcho(RNInfo & info, unsigned long animationStartMillis)
    : RNAnimation(info, animationStartMillis) {
    	// initalize the buffer to zero
    	brightness = kMinBrightness;
    	replayMode = 1;
        lastModeSwitchTimestamp = 0;
    	modeBrightness = 0;
        recordingDuration = 0;
        loopCount = 0;
    	clearHistory();
    };
    virtual void paint(RNLights & lights);
    
    virtual const char * name();

    void flash();
    void recordFlash();
    void fade();
    void clearHistory();
    void playHistory();
    void setIsReplaying(int replaying);

    int brightness;
    int modeBrightness;

    int replayMode;

    unsigned long tapHistory[historySize];
    unsigned long recordingDuration;
    unsigned long loopCount;
    int historyWriteHead;
    int historyReadHead;

    unsigned long lastModeSwitchTimestamp;
};

#endif /* defined(__FlashEcho__) */
