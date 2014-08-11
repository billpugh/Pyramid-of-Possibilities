#include "Flashes.h"
#include "Arduino.h"

void Flashes::paint(RNLights & lights) {
    unsigned long now = info.getGlobalMillis();
    if (now < lastUpdate + parameters.flashDuration) {
        return;
    }

    for (int i = 0; i < lastSize; i++) {
        lights.setPixelColor(lastLed + i, 0, 0, 0);
    }
    
    lastLed = random(lights.getNumPixels());
    lastSize = parameters.flashSize;
    for (int i = 0; i < lastSize; i++) {
        lights.setPixelColor(lastLed + i, 
                parameters.red, parameters.green, parameters.blue);
    }
    
    lastUpdate = now;
}

const char * Flashes::name() {
    return "Flashes";
}
