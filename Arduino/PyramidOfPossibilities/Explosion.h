//
//  Explosion.h
//  PlatformData
//
//

#ifndef __EXPLOSION__
#define __EXPLOSION__

#include <vector>

#include "RNAnimation.h"
#include "RNLights.h"
#include "easingSelect.h"
#include "RNGradient.h"

struct ExplosionParameters {
    short bombPlatform[3] = {2286, 1320, 4521};
    unsigned long warmupDuration = 5000;
    unsigned long coolingDuration = 3000;
    float spinMaxSpeed = 0.7;
    float shockWaveSpeed = 20;
    unsigned long shockWaveThickness = 10000;
    uint32_t shockWaveColor = 0xffffff;
};

class Explosion : public RNAnimation {
public:
    Explosion(RNInfo & info, unsigned long animationStartMillis);
    virtual void paint(RNLights & lights);
    virtual const char * name();

private:
    ExplosionParameters parameters;
    unsigned long startTime = 0;
    unsigned long explosionTime = parameters.warmupDuration;
    float ledsDistanceToBomb[240];
    float furthestLedDistance;

    uint8_t r = parameters.shockWaveColor >> 16;
    uint8_t g = parameters.shockWaveColor >> 8;
    uint8_t b = parameters.shockWaveColor;

    static float distancePointFromPoint(short * A, short * B);

    static float distancePointFromPoint(float Ax, float Ay, float Az,
            short * B);

    static float distancePointFromPoint(
            float Ax, float Ay, float Az,
            float Bx, float By, float Bz);
};

#endif /* defined(__EXPLOSION__) */
