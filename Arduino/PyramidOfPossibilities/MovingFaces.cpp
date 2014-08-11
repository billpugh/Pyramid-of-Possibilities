//
//  MovingFaces.cpp
//  PlatformData
//

#include "MovingFaces.h"
#include "Arduino.h"
#include "ledPositions.h"

MovingFaces::MovingFaces(RNInfo & info, unsigned long animationStartMillis)
: RNAnimation(info, animationStartMillis, sizeof (MovingFacesParameters),
&parameters) {
    pointA = parameters.edgePlatform1;
    pointB = parameters.edgePlatform2;
    pointC = parameters.edgePlatform4; // Top platform
    pointD = parameters.edgePlatform3;
};

void MovingFaces::paint(RNLights & lights) {

    unsigned long now = info.getGlobalMillis();

    if (now > targetTime) {
        // Rotate points A, B and D. Point C stay the top platform.
        short * backupA = pointA;
        pointA = pointB;
        pointB = pointD;
        pointD = backupA;

        startTime = now;
        targetTime = now + parameters.duration;
    }

    float ratio = (float) (now - startTime) / (float) (targetTime - startTime);
    AHEasingFunction easingFunction = getEasingFunction(parameters.easingMode,
            parameters.curveType);
    ratio = easingFunction(ratio);

    float vector[3] = {
        (pointD[0] - pointA[0]) * ratio,
        (pointD[1] - pointA[1]) * ratio,
        (pointD[2] - pointA[2]) * ratio
    };

    long a, b, c, d;
    getPlanEquation(
            pointA[0] + vector[0], pointA[1] + vector[1], pointA[2] + vector[2],
            pointB[0], pointB[1], pointB[2],
            pointC[0], pointC[1], pointC[2],
            a, b, c, d);

    for (int i = 0; i < lights.getNumPixels(); i++) {
        float xLED = getLEDXPosition(i) + info.x;
        float yLED = getLEDYPosition(i) + info.y;
        float zLED = info.z;
        long distance = distancePointFromPlan(
                a, b, c, d,
                xLED, yLED, zLED);

        if (abs(distance) < parameters.thickness) {
            lights.setPixelColor(i,
                    parameters.red, parameters.green, parameters.blue);
        }
    }

    lastUpdate = now;
}

void MovingFaces::getPlanEquation(
        long Ax, long Ay, long Az,
        long Bx, long By, long Bz,
        long Cx, long Cy, long Cz,
        long &a, long &b, long &c, long&d) {
    a = (By - Ay) * (Cz - Az) - (Cy - Ay) * (Bz - Az);
    b = (Bz - Az) * (Cx - Ax) - (Cz - Az) * (Bx - Ax);
    c = (Bx - Ax) * (Cy - Ay) - (Cx - Ax) * (By - Ay);
    d = -(a * Ax + b * Ay + c * Az);
}

long MovingFaces::distancePointFromPlan(long a, long b, long c, long d,
        long Px, long Py, long Pz) {
    float denom = sqrt((float) (a * a + b * b + c * c));
    return (a * Px + b * Py + c * Pz + d) / denom;
}

long MovingFaces::distancePointFromPlan(
        long Px, long Py, long Pz,
        long Ax, long Ay, long Az,
        long Bx, long By, long Bz,
        long Cx, long Cy, long Cz) {
    long a, b, c, d;
    getPlanEquation(Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz, a, b, c, d);
    float denom = sqrt((float) (a * a + b * b + c * c));

    return (a * Px + b * Py + c * Pz + d) / denom;
}

const char * MovingFaces::name() {
    return "MovingFaces";
}
