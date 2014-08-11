//
//  MovingFaces.h
//  PlatformData
//
//

#ifndef __MOVINGFACES__
#define __MOVINGFACES__

#include "RNAnimation.h"
#include "RNLights.h"

struct MovingFacesParameters {
    short edgePlatform1[3] = {0, 7919, 762};
    short edgePlatform2[3] = {-6858, -3959, 610};
    short edgePlatform3[3] = {6858, -3959, 686};
    short edgePlatform4[3] = {0, 0, 9144};
    uint8_t red = 255;
    uint8_t green = 255;
    uint8_t blue = 255;
    unsigned long duration = 1000;
    int thickness = 800;
};

class MovingFaces : public RNAnimation {
public:
    MovingFaces(RNInfo & info, unsigned long animationStartMillis);
    virtual void paint(RNLights & lights);
    virtual const char * name();

private:
    MovingFacesParameters parameters;
    unsigned long lastUpdate = 0;
    unsigned long startTime = 0;
    unsigned long targetTime = parameters.duration;
    short * pointA;
    short * pointB;
    short * pointC;
    short * pointD;

    /**
     * Get the equation of the plan defined by the points ABC in the form
     * ax + by + cz + d = 0
     */
    static void getPlanEquation(
            long Ax, long Ay, long Az,
            long Bx, long By, long Bz,
            long Cx, long Cy, long Cz,
            long &a, long &b, long &c, long &d);

    /**
     * Get the distance between the point P and the plan defined by the
     * equation ax + by + cz + d = 0
     */
    static long distancePointFromPlan(
            long Px, long Py, long Pz,
            long a, long b, long c, long d);

    /**
     * Compute the distance between the point P and the plan ABC
     */
    static long distancePointFromPlan(
            long Px, long Py, long Pz,
            long Ax, long Ay, long Az,
            long Bx, long By, long Bz,
            long Cx, long Cy, long Cz);
};

#endif /* defined(__MOVINGFACES__) */
