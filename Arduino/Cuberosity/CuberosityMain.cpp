//
//  CuberosityMain.cpp
//  Cuberosity
//
//  Created by Bill on 6/4/15.
//
//

#include "CuberosityMain.h"
#include <stdio.h>
#include "Arduino.h"
#include "Animation.h"
#include "Animations.h"

DMAMEM int displayMemory[LEDsPerStrip * 6];
int drawingMemory[LEDsPerStrip * 6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(LEDsPerStrip, displayMemory, drawingMemory, config);

const int animationDuration = 10000;

unsigned long switchAnimationAt;
void setupMain() {
    Serial.begin(9600);
    leds.begin();
    leds.show();
    delay(2000);
    switchAnimationAt = millis() + animationDuration;
    Serial.print("Now ");
    Serial.println(millis());
    Serial.print("switch at ");
    Serial.println(switchAnimationAt);
    
}
AnimationEnum program = firstAnimation();

Animation *currentAnimation = getAnimation(program);

void iterateAll() {
    currentAnimation->prepare();
    for(int side = 0; side < 3; side++) {
        int stripStart =side*2*LEDsPerStrip;
        for(int i = 0; i < horizontalLength; i++)
            currentAnimation->setPixel(stripStart + i, side, 0, -1-i);
        stripStart += horizontalLength + horizontalGap;
        for(int i = 0; i < horizontalLength; i++)
            currentAnimation->setPixel(stripStart + i, (side+1)%3, 0, horizontalLength-i);
        stripStart += horizontalLength;
        for(int i = 0; i < verticalLength; i++)
            currentAnimation->setPixel(stripStart + i, (side+1)%3, i+1, 0);
        
        // do down size
        stripStart = side*2*LEDsPerStrip + LEDsPerStrip;
        for(int i = 0; i < verticalLength; i++)
            currentAnimation->setPixel(stripStart + i, side, -1-i, 0);
        
    }
}


void loopMain() {
    if (millis() > switchAnimationAt) {
        Serial.print("Changing animation ");
        delete currentAnimation;
        program = nextAnimation(program);
        currentAnimation = getAnimation(program);
        switchAnimationAt = millis() + animationDuration;
    }
    iterateAll();
    leds.show();
    
}
