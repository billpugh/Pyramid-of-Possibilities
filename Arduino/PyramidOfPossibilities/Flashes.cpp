#include "Flashes.h"
#include "Arduino.h"

void Flashes::paint(RNLights & lights) {
    unsigned long now = info.getGlobalMillis();
    if (now < lastUpdate + parameters.flashDuration) {
        return;
    }

    int led = random(lights.getNumPixels());
    for (int i = 0; i < parameters.flashSize; i++) {
        lights.setPixelColor(led + i, 255, 255, 255);
    }
    
    lastUpdate = now;
}

const char * Flashes::name() {
    return "Flashes";
}
