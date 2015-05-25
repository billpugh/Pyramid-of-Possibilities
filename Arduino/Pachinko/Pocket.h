//
//  Pocket.h
//  PachinkoTestbed
//
//  Created by Bill on 5/10/15.
//
//

#ifndef __PachinkoTestbed__Pocket__
#define __PachinkoTestbed__Pocket__

#include <stdio.h>
#include "OctoWS2811.h"
#include "Adafruit_MCP23017.h"

class Pocket {
public:
    Pocket(OctoWS2811 & lights, int firstPixel, Adafruit_MCP23017 & io, int sensor, int pointValue);
    
    void begin();
    void shiftUp(int fill);
    void shiftDown(int fill);

    /** Return true if score detected */
    bool checkAndUpdate();
    /** Return true if score detected */
    bool checkSensor();
    void gameOver();
    
    static const int LEDS_PER_POCKET = 5+6+7+6+5;
    
private:
    static const unsigned long DEBOUNCE_TIME = 30;
    static const unsigned long TOO_LONG_CLOSED_TIME = 2000;
    OctoWS2811 & lights;
    const int firstPixel;
    Adafruit_MCP23017 & io;
    const int sensor;
    const int pointValue;
    
    
    // strips are numbered -2 ... +2
    // positions are numbered 0..6
    
    int getLED(int strip, int pos);
    void setColorAll(int rgb);
    void setColor(int strip, int pos, int rgb);

    
    unsigned long lastTimeChanged;
    unsigned long lastTimeScored;
    unsigned long lastAnimationUpdate;
    bool state;
    public:
    int rgb;
    int strip;
    int pos;
    
};



#endif /* defined(__PachinkoTestbed__Pocket__) */
