//
//  Pocket.cpp
//
//  Created by Bill on 5/10/15.
//
//


#include <stdlib.h>
#include "Pocket.h"
#include "PachinkoMain.h"

Pocket::Pocket(OctoWS2811 & lights, int firstPixel, Adafruit_MCP23017 &io,  int sensor) : lights(lights), firstPixel(firstPixel), io(io), sensor(sensor), lastTimeChanged(0), lastTimeScored(-5000) {
    
};


/** Return true if score detected */
bool Pocket::checkSensor() {
    unsigned long now = millis();
    if (lastTimeChanged + DEBOUNCE_TIME > now) {
        // too soon, not going to change anything
        return false;
    }
    bool sensorState = false;
    bool change = sensorState == state;
    if (change) {
        state =  sensorState;
        lastTimeChanged = now;
        return state;
    } else if (state && lastTimeChanged + TOO_LONG_CLOSED_TIME < now) {
        // been closed for more than 2 seconds
        // signal this somehow
        
    }
    return false;
}

// strips are numbered -2 ... +2
// positions are numbered 0..6

static int offsets[] = {0, 5, 11, 18, 24};

int Pocket::getLED(int strip, int pos) {
    if (strip < -2 || strip > 2)
        return -1;
    int maxLED = 6 - abs(strip);
    if (pos < 0 || pos > maxLED)
        return -1;
    return offsets[strip+2]+pos;
}

void Pocket::setColorAll(int rgb) {
    for(int i = 0; i < LEDS_PER_POCKET; i++)
        lights.setPixel(i, rgb);
}

void Pocket::setColor(int strip, int pos, int rgb) {
    int pixel = getLED(strip, pos);
    if (pixel < 0) return;
    lights.setPixel(pixel, rgb);
}


void Pocket::gameOver() {
    setColorAll(0);
}
bool Pocket::checkAndUpdate() {
    if (pachinkoState == e_GameOver) {
        gameOver();
        return false;
    }
    bool scoreDetected = checkSensor();
    if (scoreDetected) {
        lastTimeScored = millis();
        scorePoints(1);
    }
    return scoreDetected;
}