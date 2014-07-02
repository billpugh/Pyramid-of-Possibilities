/* 
 * File:   PyramidArchitecture.cpp
 * Author: antoine
 * 
 * Created on June 30, 2014, 7:33 PM
 */

#include "PyramidArchitecture.hpp"
#include "platforms.h"
#include "tier.h"
#include "model.h"
#include "leds.h"

void PyramidArchitecture::getLocationOfPlatform(int platform, 
        short* &location) {
    location = platformPositions[platform];
}

short PyramidArchitecture::getTierOfPlatform(int platform) {
    return tier[platform];
}

void PyramidArchitecture::getVertices(float* &vertices) {
    vertices = popVerts;
}

void PyramidArchitecture::getNormals(float* &normals) {
    normals = popNormals;
}

unsigned int PyramidArchitecture::getNumVertices() {
    return popNumVerts;
}

void PyramidArchitecture::getLedPosition(int led, short *&position) {
    position = ledPositions[led];
}
