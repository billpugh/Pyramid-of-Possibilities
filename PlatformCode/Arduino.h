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
 void interrupts();
 void noInterrupts();
 void delay(uint16_t millis);
 void digitalWrite(uint8_t ONBOARD_LED_PIN, bool LOW);

#define OUTPUT 1
#define HIGH 1
#define LOW 0

#ifndef max
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#endif


 int random(int max);


class SerialClass {
public:
    void println();
    void print();
    void begin(int baudRate);
    void print(const char * s);
    void println(const char * s);
    void println(int);
    void print(int);
    unsigned int readBytes( char *buffer, unsigned int length);
    uint16_t available();
    uint8_t read();
};

extern SerialClass Serial;
extern SerialClass Serial2;

#endif
