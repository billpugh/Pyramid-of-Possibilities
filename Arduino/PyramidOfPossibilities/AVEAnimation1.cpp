//
//  AVEAnimation1.cpp
//  PlatformData
//

#include "AVEAnimation1.h"

AVEAnimation1::AVEAnimation1(RNInfo& info, unsigned long animationStartMillis)
: RNAnimation(info, animationStartMillis) {
    forward = info.direction==1;
    lastUpdate = 0;
    currentPos = 0;
}

void AVEAnimation1::paint(RNLights & lights) {
    unsigned long ms = getAnimationMillis();
    if (ms - lastUpdate < 100) {
        return;
    }
    int direction = forward ? 1 : -1;

    currentPos += direction;
    currentPos = lights.normalize(currentPos);
    for (int i = 0; i <= 100; i++) {
        int intensity = 255 - 2.55 * i;
        int pos = lights.normalize(currentPos - i * direction);
        lights.setPixelColor(pos, intensity, intensity, intensity);
    }
    info.showActivityWithBrightness(lights, 128);
}

const char * AVEAnimation1::name() {
    return "AVEAnimation1";
}
