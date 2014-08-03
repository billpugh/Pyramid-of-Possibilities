/* 
 * File:   PyramidArchitecture.hpp
 * Author: antoine
 *
 * Created on June 30, 2014, 7:33 PM
 */

#ifndef PYRAMIDARCHITECTURE_HPP
#define	PYRAMIDARCHITECTURE_HPP

#include <stdint.h>

class PyramidArchitecture {
public:
    static const int nbPlatforms = 84;
    static const int nbLedsPerPlatform = 220;
    
    static void getLocationOfPlatform(int platform, short* &location);

    static short getTierOfPlatform(int platform);

    static int getPlatformNumberOnTier(int platform);
    
    static void getVertices(float* &popVerts);

    static void getNormals(float* &popNormals);

    static unsigned int getNumVertices();

    static void getLedPosition(uint8_t led, int16_t &x, int16_t &y);
private:

};

#endif	/* PYRAMIDARCHITECTURE_HPP */

