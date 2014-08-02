#include "AVEFlashesAnimation.h"
#include "Arduino.h"

AVEFlashesAnimation::AVEFlashesAnimation(RNInfo& info, unsigned long animationStartMillis)
: RNAnimation(info, animationStartMillis) {
}

void AVEFlashesAnimation::paint(RNLights & lights) {
    lights.setAllPixelColors(0, 0, 0);
    
    int led = random(lights.getNumPixels());
    
    lights.setPixelColor(led, 255, 255, 255);
}

const char * AVEFlashesAnimation::name() {
    return "AVEFlashesAnimation";
}
