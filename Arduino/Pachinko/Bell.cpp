//
//  Bell.cpp
//  PachinkoTestbed
//
//  Created by Bill on 5/17/15.
//
//

#include "Bell.h"




Bell::Bell(Adafruit_MCP23017 & io, int pin, int durationOn) : io(io), pin(pin), durationOn(durationOn),
enqueued(0), on(false), timeOff(0) {
    
}


void Bell::update() {
    if (on) {
        if (millis() > timeOff) {
            on = false;
            io.digitalWrite(pin, 0);
        }
    } else if (enqueued > 0 && millis() > timeOff + durationOn) {
        on = true;
        io.digitalWrite(pin, 1);
        timeOff = millis() + durationOn;
    }
    
}
void Bell::turnOn() {
    enqueued++;
    
}