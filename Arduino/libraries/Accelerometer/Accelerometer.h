#ifndef __Accelerometer__
#define __Accelerometer__

#include <stdint.h>
#include <stdlib.h>




void initializeAccelerometer(
                             bool highPassFilter = true,
                             uint8_t PULSE_THSX = 1,
                             uint8_t PULSE_THSY = 1,
                             uint8_t PULSE_THSZ = 1);


void getAccelerometerData( float &totalG,
                          float directionalG[3],
                          uint8_t &tapSource);


void readAccelData(int16_t * destination);

#endif /* defined(__Accelerometer__) */

