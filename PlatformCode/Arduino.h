//
//  Arduino.h
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef PlatformData_Arduino_h
#define PlatformData_Arduino_h

#include <stdint.h>

 unsigned long millis();
 unsigned long micros();

#ifndef max
#define abs(x) ((x)>0?(x):-(x))
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#endif

 int random(int max);


class SerialClass {
public:
    void println();
    void print();
    void print(const char * s);
    void println(const char * s);
    uint16_t available();
    uint8_t read();
};

extern SerialClass Serial;
extern SerialClass Serial2;

#endif
