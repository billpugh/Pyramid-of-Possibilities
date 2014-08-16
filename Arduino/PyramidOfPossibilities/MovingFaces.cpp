//
//  MovingFaces.cpp
//  PlatformData
//

#include "MovingFaces.h"
#include "Arduino.h"
#include "ledPositions.h"
#include <math.h>

MovingFaces::MovingFaces(RNInfo & info, unsigned long animationStartMillis)
: RNAnimation(info, animationStartMillis, sizeof (MovingFacesParameters),
&parameters), gradient3Colors(info.numLEDs) {
    pointA = parameters.edgePlatform1;
    pointB = parameters.edgePlatform2;
    pointC = parameters.edgePlatform4; // Top platform
    pointD = parameters.edgePlatform3;

    if (parameters.summitColorMode) {
        for (int i = 0; i < info.numLEDs; i++) {
            float xLED = getLEDXPosition(i) + info.x;
            float yLED = getLEDYPosition(i) + info.y;
            float zLED = info.z;
            float dist1 = distancePointFromPoint(xLED, yLED, zLED,
                    parameters.edgePlatform1);
            float dist2 = distancePointFromPoint(xLED, yLED, zLED,
                    parameters.edgePlatform2);
            float dist3 = distancePointFromPoint(xLED, yLED, zLED,
                    parameters.edgePlatform3);
            float totalDist = dist1 + dist2 + dist3;

            float normD1 = dist1 / totalDist;
            float normD2 = dist2 / totalDist;
            float normD3 = dist3 / totalDist;

            float ratio1;
            float ratio2;
            float ratio3;

            if (normD1 != 0 && normD2 != 0 && normD3 != 0) {
                ratio1 = 1 / normD1;
                ratio2 = 1 / normD2;
                ratio3 = 1 / normD3;
            } else {
                ratio1 = normD1 == 0 ? 1 : 0;
                ratio2 = normD2 == 0 ? 1 : 0;
                ratio3 = normD3 == 0 ? 1 : 0;
            }

            float totalRatios = ratio1 + ratio2 + ratio3;
            float normRatio1 = ratio1 / totalRatios;
            float normRatio2 = ratio2 / totalRatios;
            float normRatio3 = ratio3 / totalRatios;

            uint32_t color = mixColors(parameters.summit1Color, normRatio1,
                    parameters.summit2Color, normRatio2,
                    parameters.summit3Color, normRatio3);
            gradient3Colors.setPixelColor(i, color);
        }
    }
};

void MovingFaces::paint(RNLights & lights) {

    unsigned long now = info.getGlobalMillis();

    if (now > targetTime) {
        // Rotate points A, B and D. Point C stay the top platform.
        short * backupA = pointA;
        pointA = pointB;
        pointB = pointD;
        pointD = backupA;

        distanceAD = distancePointFromPoint(pointA, pointD);
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

        if (parameters.summitColorMode) {
            if (abs(distance) <= parameters.thickness) {
                lights.setPixelColor(i, gradient3Colors.getPixelColor(i));
            }
        } else {
            RNGradient *gradientToUse = 0;
            float point = 0;
            if (abs(distance) <= parameters.thickness) {
                gradientToUse = &(parameters.gradientInside);
                point = (float) (parameters.thickness - abs(distance)) /
                        (float) parameters.thickness;
            } else {
                gradientToUse = &(parameters.gradientOutside);
                point = (float) abs(distance) / (float) distanceAD;
            }
            uint32_t color = gradientToUse->getColor(point * 255);
            lights.setPixelColor(i, color);
        }
    }

    lastUpdate = now;
}

uint32_t MovingFaces::mixColors(uint32_t color1, float ratio1,
        uint32_t color2, float ratio2,
        uint32_t color3, float ratio3) {
    uint8_t red = ((uint8_t) (color1 >> 16)) * ratio1 +
            ((uint8_t) (color2 >> 16)) * ratio2 +
            ((uint8_t) (color3 >> 16)) * ratio3;
    uint8_t green = ((uint8_t) (color1 >> 8)) * ratio1 +
            ((uint8_t) (color2 >> 8)) * ratio2 +
            ((uint8_t) (color3 >> 8)) * ratio3;
    uint8_t blue = ((uint8_t) color1) * ratio1 +
            ((uint8_t) color2) * ratio2 +
            ((uint8_t) color3) * ratio3;

    uint8_t max = max(red, max(green, blue));
    if (max != 0) {
        red *= 255.0 / max;
        green *= 255.0 / max;
        blue *= 255.0 / max;
    }

    return (red << 16) | (green << 8) | blue;
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

float MovingFaces::distancePointFromPlan(long a, long b, long c, long d,
        long Px, long Py, long Pz) {
    float denom = sqrt((float) (a * a + b * b + c * c));
    return (a * Px + b * Py + c * Pz + d) / denom;
}

float MovingFaces::distancePointFromPlan(
        long Px, long Py, long Pz,
        long Ax, long Ay, long Az,
        long Bx, long By, long Bz,
        long Cx, long Cy, long Cz) {
    long a, b, c, d;
    getPlanEquation(Ax, Ay, Az, Bx, By, Bz, Cx, Cy, Cz, a, b, c, d);
    return distancePointFromPlan(Px, Py, Pz, a, b, c, d);
}

float MovingFaces::distancePointFromPoint(short * A, short * B) {
    return distancePointFromPoint(A[0], A[1], A[2], B[0], B[1], B[2]);
}

float MovingFaces::distancePointFromPoint(float Ax, float Ay, float Az,
        short * B) {
    return distancePointFromPoint(Ax, Ay, Az, B[0], B[1], B[2]);
}

float MovingFaces::distancePointFromPoint(
        float Ax, float Ay, float Az,
        float Bx, float By, float Bz) {
    long x = Ax - Bx;
    long y = Ay - By;
    long z = Az - Bz;
    return sqrt(x * x + y * y + z * z);
}

const char * MovingFaces::name() {
    return "MovingFaces";
}
