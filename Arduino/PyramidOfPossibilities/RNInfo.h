//
//  RNInfo.h
//  PlatformData
//
//  Created by Bill on 7/17/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __PlatformData__RNInfo__
#define __PlatformData__RNInfo__

#include <stdint.h>

const static uint8_t numLEDs = 220;

class RNInfo {
public:
  RNInfo(
  uint8_t numLEDs,
  uint8_t tier,
  uint8_t number,
  uint8_t identifier,
  int16_t x,
  int16_t y,
  int16_t z);


  // Information about the platform
  // Number of visible LEDs on the platform
  const uint8_t numLEDs;
  // What tier is the platform on
  const uint8_t tier;
  // What is the number of the platform within that tier
  const uint8_t number;
  // What is the identify of the platform (unique)
  const uint8_t identifier;

  // What is the x,y,z displacement of the center of the platform 
  // from the center base of the Pyramid
  const int16_t x,y,z;
  // Get the global clock value (synchronized across all platforms)
  unsigned long getGlobalMillis();

  // Get the most recent reading from the accelerometer, combine all three axes. 
  // Non-negative, passed through a high pass filter, will be 0.0 when everything is absolutely still.
  float getLocalActitiviity();
  // Get the individual x,y,z accelerometer readings passed through a high pass filter. Values may be negative. 
  void getLocalXYZActitiviity(float data[3]);
  // Get whether or not taps have been detected since the last paint refresh. If zero, no taps have been indicated. 
  // This is a bit field, with different bits indicating whether the tap was in the X, Y or Z direction, 
  // and whether it was positive or negative. In most cases, it is sufficient to check whether or not this value is nonzero.
  // Bits are: 
  // AxX: 0x10 -- tap in X axis
  // PxX: 0x01 -- positive in X axis
  // AxY: 0x20 -- tap in Y axis
  // PxY: 0x02 -- positive in Y axis
  // AxZL 0x40 -- tap in Z axis
  // PxZ: 0x04 -- positive in Z axis
  uint8_t getTaps();

  // get the number of milliseconds since the last tap
  unsigned long timeSinceLastTap();

  // Get a combined indication of activity across all platforms. Same scale as getLocalActivity
  float getGlobalActivity();

  // getGlobalAngle for LED in degrees (0 = south)
  uint16_t getGlobalAngle(uint8_t led);

private:
  uint8_t globalAngle[240];


};


#endif /* defined(__PlatformData__RNInfo__) */



