#include "RNShowChaser.h"
#include <Arduino.h>

RNShowChaser::RNShowChaser(RNLights & lights) : RNShow(lights) {
}

RNShowChaser::~RNShowChaser() {
}


void RNShowChaser::accelerometerCallback( float totalG,
float directionalG[3],
uint8_t tapSource) {
  if (tapSource)
    tapStrength = totalG;
}

uint8_t RNShowChaser::currentHue() {
  return (getMillis() / 100) % 256;
}

void RNShowChaser::addChaser() {

  if (nextChaser > getMillis())  return;

  uint16_t v = 50+tapStrength*200+random(50);
  if (v > 255)
    v = 255;
  nextChaser = getMillis() + 300;
  int c = random(numChasers);
  if (!chaser[c].active) {
    if (tapStrength < 0.2 && random(4) != 1)
      chaser[c].hsv.h = currentHue();
    else 
      chaser[c].hsv.h = random(256);
    chaser[c].hsv.s  = 255;
    chaser[c].brightness = v;


    int rpm;
    if (tapStrength > 0.5 && random(6) == 0)
      rpm = 30 + random(40);
    else
      rpm = 10 + random(30);

    chaser[c].setRPM(rpm);
    chaser[c].position = random(lights.getNumPixels());
    chaser[c].forward = random(2) != 0;
    chaser[c].activate(getMillis());
  } 

}



