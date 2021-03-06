/* 
 * File:   Arduino.h
 * Author: antoine
 *
 * Created on August 2, 2014, 2:21 PM
 */

#ifndef ARDUINO_H
#define	ARDUINO_H

#define DEBUG 1

#define POP_SIMULATOR

// Give abs function
#include <stdlib.h>
#include <math.h>

#ifndef max
#define max(x,y) ((x)>(y)?(x):(y))
#define min(x,y) ((x)<(y)?(x):(y))
#endif

unsigned long millis();

unsigned long micros();

int random(int max);

#endif	/* ARDUINO_H */

