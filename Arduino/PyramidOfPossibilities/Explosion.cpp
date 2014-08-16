//
//  Explosion.cpp
//  PlatformData
//

#include <vector>

#include "Explosion.h"
#include "Arduino.h"
#include "ledPositions.h"
#include <math.h>

Explosion::Explosion(RNInfo & info, unsigned long animationStartMillis)
: RNAnimation(info, animationStartMillis, sizeof (ExplosionParameters),
&parameters), ledsDistanceToBomb() {

    furthestLedDistance = 0;
    for (int i = 0; i < info.numLEDs; i++) {
        int16_t x = getLEDXPosition(i);
        int16_t y = getLEDYPosition(i);
        float distPlatform = sqrt(x * x + y * y);
        furthestLedDistance = max(furthestLedDistance, distPlatform);
        float xLED = x + info.x;
        float yLED = y + info.y;
        float zLED = info.z;
        float dist = distancePointFromPoint(xLED, yLED, zLED,
                parameters.bombPlatform);
        ledsDistanceToBomb[i] = dist;
    }
};

void Explosion::paint(RNLights & lights) {

    unsigned long now = info.getGlobalMillis();

    if (now > explosionTime + parameters.coolingDuration) {
        explosionTime = now + parameters.warmupDuration;
        startTime = now;
    }

    if (now < explosionTime) {
        if (info.x == parameters.bombPlatform[0] &&
                info.y == parameters.bombPlatform[1] &&
                info.z == parameters.bombPlatform[2]) {

            float ratio = (float) (now - startTime) /
                    (float) (explosionTime - startTime);
            float speed = parameters.spinMaxSpeed * ratio;
            int position = speed * (now - startTime);
            for (int i = 0; i <= 100; i++) {
                float intensity = 1 - i / 100.0;
                int pos = lights.normalize(position - i);
                lights.setPixelColor(pos,
                        r * intensity, g * intensity, b * intensity);
            }
        }
        return;
    }

    float shockWaveDistance = furthestLedDistance +
            (now - explosionTime) * parameters.shockWaveSpeed;

    AHEasingFunction shockwaveEasing = getEasingFunction(EaseIn, CurveTypeExpo);
    float endShockWave = shockWaveDistance - parameters.shockWaveThickness;
    for (int i = 0; i < info.numLEDs; i++) {
        float distance = ledsDistanceToBomb[i];
        if (endShockWave <= distance &&
                distance <= shockWaveDistance) {
            float ratio = 1 - (shockWaveDistance - distance) /
                    parameters.shockWaveThickness;
            ratio = shockwaveEasing(ratio);

            lights.setPixelColor(i, r * ratio, g * ratio, b * ratio);
        }
    }
}

float Explosion::distancePointFromPoint(short * A, short * B) {
    return distancePointFromPoint(A[0], A[1], A[2], B[0], B[1], B[2]);
}

float Explosion::distancePointFromPoint(float Ax, float Ay, float Az,
        short * B) {
    return distancePointFromPoint(Ax, Ay, Az, B[0], B[1], B[2]);
}

float Explosion::distancePointFromPoint(
        float Ax, float Ay, float Az,
        float Bx, float By, float Bz) {
    long x = Ax - Bx;
    long y = Ay - By;
    long z = Az - Bz;
    return sqrt(x * x + y * y + z * z);
}

const char * Explosion::name() {
    return "Explosion";
}
