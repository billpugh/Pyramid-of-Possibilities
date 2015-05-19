//
//  Bell.h
//  PachinkoTestbed
//
//  Created by Bill on 5/17/15.
//
//

#ifndef __PachinkoTestbed__Bell__
#define __PachinkoTestbed__Bell__

#include <stdio.h>

#include "Adafruit_MCP23017.h"

class Bell {
public:
    Bell(Adafruit_MCP23017 & io, int pin, int durationOn, int durationOff);
    void begin();
   void update();
   void ring(int num=1);
    
private:
    
    Adafruit_MCP23017 & io;

    const int pin;
    const int durationOn;
    const int durationOff;
    unsigned int enqueued;
    bool on;
    unsigned long timeOff;
    
    
};



#endif /* defined(__PachinkoTestbed__Bell__) */
