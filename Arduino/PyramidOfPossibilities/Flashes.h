/* 
 * File:   AVEFlashesAnimation.h
 * Author: antoine
 *
 * Created on August 2, 2014, 4:50 PM
 */

#ifndef FLASHES_H
#define	FLASHES_H

#include "RNAnimation.h"
#include "RNLights.h"

struct FlashesParameters {
    uint16_t flashDuration = 100; // flash duration in ms
    uint8_t flashSize = 3; // Nb pixels per flash
    uint8_t red = 255;
    uint8_t green = 255;
    uint8_t blue = 255;
};

class Flashes : public RNAnimation {
public:

    Flashes(RNInfo & info, unsigned long animationStartMillis)
            : RNAnimation(info, animationStartMillis, sizeof(FlashesParameters),
                    &parameters) {};
    virtual void paint(RNLights & lights);
    virtual const char * name();

private:
    FlashesParameters parameters;
    unsigned long lastUpdate = 0;
};

#endif	/* FLASHES_H */

