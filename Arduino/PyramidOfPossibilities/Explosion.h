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
    short bombPlatform[3] = {0, 0, 9144};
    unsigned long warmupDuration = 3000;
    unsigned long coolingDuration = 3000;
    float shockWaveSpeed = 20;
    unsigned long shockWaveThickness = 10000;
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
    std::vector<float> ledsDistanceToBomb;
    float furthestLedDistance;

    static float distancePointFromPoint(short * A, short * B);

    static float distancePointFromPoint(float Ax, float Ay, float Az,
            short * B);

    static float distancePointFromPoint(
            float Ax, float Ay, float Az,
            float Bx, float By, float Bz);
};

#endif /* defined(__EXPLOSION__) */
