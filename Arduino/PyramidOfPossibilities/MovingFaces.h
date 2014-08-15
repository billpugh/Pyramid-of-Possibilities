//
//  MovingFaces.h
//  PlatformData
//
//

#ifndef __MOVINGFACES__
#define __MOVINGFACES__

#include "RNAnimation.h"
#include "RNLights.h"
#include "easingSelect.h"
#include "RNGradient.h"

struct MovingFacesParameters {
    short edgePlatform1[3] = {0, 7919, 762};
    short edgePlatform2[3] = {-6858, -3959, 610};
    short edgePlatform3[3] = {6858, -3959, 686};
    short edgePlatform4[3] = {0, 0, 9144};
    RNGradient gradientInside = RNGradient(0, RNGradientCapped, 0x000000, 0x00ff00);
    RNGradient gradientOutside = RNGradient(0, RNGradientCapped, 0x000002, 0x000002);
    bool summitColorMode = true;
    uint32_t summit1Color = 0xff0000;
    uint32_t summit2Color = 0x00ff00;
    uint32_t summit3Color = 0x0000ff;
    unsigned long duration = 1000;
    int thickness = 800;
    EasingMode easingMode = EaseInOut;
    CurveType curveType = CurveTypeQuadratic;
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
    float distanceAD;
    RNLights gradient3Colors;

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
    static float distancePointFromPlan(
            long Px, long Py, long Pz,
            long a, long b, long c, long d);

    /**
     * Compute the distance between the point P and the plan ABC
     */
    static float distancePointFromPlan(
            long Px, long Py, long Pz,
            long Ax, long Ay, long Az,
            long Bx, long By, long Bz,
            long Cx, long Cy, long Cz);
    
    static float distancePointFromPoint(short * A, short * B);
    
    static float distancePointFromPoint(float Ax, float Ay, float Az,
        short * B);
    
    static float distancePointFromPoint(
        float Ax, float Ay, float Az,
        float Bx, float By, float Bz);
    
    static uint32_t mixColors(uint32_t color1, float ratio1,
        uint32_t color2, float ratio2,
        uint32_t color3, float ratio3);
};

#endif /* defined(__MOVINGFACES__) */
