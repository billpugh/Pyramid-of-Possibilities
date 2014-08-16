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

// White default
struct FlashesParameters {
    uint16_t flashDuration = 100; // flash duration in ms
    uint8_t flashSize = 3; // Nb pixels per flash
    uint8_t red = 255;
    uint8_t green = 255;
    uint8_t blue = 255;
    uint8_t numFlashes = 1;
};

// Seizure
//struct FlashesParameters {
//    uint16_t flashDuration = 100; // flash duration in ms
//    uint8_t flashSize = 5; // Nb pixels per flash
//    uint8_t red = 255;
//    uint8_t green = 255;
//    uint8_t blue = 255;
//    uint8_t numFlashes = 12;
//};

// Hyper Green Seizure
//struct FlashesParameters {
//    uint16_t flashDuration = 20; // flash duration in ms
//    uint8_t flashSize = 220; // Nb pixels per flash
//    uint8_t red = 100;
//    uint8_t green = 255;
//    uint8_t blue = 0;
//    uint8_t numFlashes = 1;
//};

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

