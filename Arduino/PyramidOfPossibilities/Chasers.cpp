//
//  Chasers.cpp
//  PlatformData
//
//  Created by Bill on 7/18/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Chasers.h"
#include <Arduino.h>
#include "Constants.h"

static CHSV hsv;
static CRGB rgb;

Chasers::Chasers(RNInfo & info, AnimationInfo animationInfo)
: 
RNAnimation(info, animationInfo), lights(info.numLEDs), dots(info.numLEDs) {

  for(int i = 0; i < numChasers; i++) {
    chaser[i].active = false;
  }

  lastUpdate = animationInfo.startTime;
  lights.setFade(animationInfo.startTime, 500);
  dots.setFade(animationInfo.startTime, 750);
};

const char * Chasers:: name() {
  return "Chasers";
}



uint8_t Chasers::currentHue() {
  return (getAnimationMillis() / 100) % 256;
}
void Chasers::setRandomPixel(float v) {
  int pixel = random(lights.getNumPixels());

  int brightness = dots.getPixelRed(pixel) 
    + dots.getPixelGreen(pixel) 
      + dots.getPixelBlue(pixel);

//    info.printf("brightness %d\n", brightness);
  if (brightness > 50)
    hsv.v = 50*v;
  else
    hsv.v = 75*v+25;
  hsv.s = 255;
  hsv.h = currentHue();
  hsv2rgb_rainbow(hsv,rgb);

  dots.setPixelColor(pixel, rgb.r, rgb.g, rgb.b);
  lights.setPixelColor(pixel, rgb.r, rgb.g, rgb.b);

//    info.printf("brightness %d: %d %d %d\n", brightness, rgb.r, rgb.g, rgb.b);

}

void Chasers::addChaser() {


  if (nextChaser > getAnimationMillis())  return;
  info.printf("addChaser\n");
  uint16_t v = 50+tapStrength*200+random(50);
  if (v > 255)
    v = 255;
  if (DEBUG)
    info.printf("Chaser v %d\n", v);
  nextChaser = getAnimationMillis() + 300;
  int c = random(numChasers);
  if (!chaser[c].active) {
    if (DEBUG)
      info.printf("Activating chaser %d\n", c);
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

    if (DEBUG) {
      info.printf("%3d %4d  ", rpm, chaser[c].delay);
      info.printf("%3d %3d %3d  %f\n", chaser[c].hsv.h,chaser[c].hsv.s, chaser[c].hsv.v, chaser[c].fadeValue);
    }
    chaser[c].position = random(lights.getNumPixels());
    chaser[c].forward = random(2) != 0;
    chaser[c].activate(getAnimationMillis());
  } 
  else {
    if (DEBUG)
      info.printf("chaser %d already active\n", c);
  }
  info.printf("chaser added\n");
}

void Chasers::tap(float v) {
  if (v >= 1.0) {
    v = 0.5;
    didTap = true;
    taps++;
  } 
  else {
    jiggles ++;
    totalJiggle += v;
  }
  int num = v*info.numLEDs/5;
  if (num < 1)
    num = 1;
  for(int i = 0; i < num; i++) {
    setRandomPixel(v);
  }
}


void Chasers::paint(RNLights & paintMe) {
  unsigned long ms = getAnimationMillis();
  float totalG = info.getLocalActivity();
  if (lastUpdate > ms-20)
    lastUpdate = ms-20;

  while (lastUpdate + 7 < ms) {
    lastUpdate += 7;


    if (totalG > 0.01) {
      float num = totalG*5+0.1;
      if (num >= 1)
        num = 0.99; 
      tap(num);
    }
    if (random(5) == 0)
      setRandomPixel(0.1);
    else if (random(10) == 0)
      setRandomPixel(0.3);
    else if (random(400) == 0) {
      tapStrength = 0.0;
      addChaser();
    }
  }

  if (info.getTaps() || hasBeenTweaked()) {
    if (DEBUG) info.printf("Saw tap %x %f\n", info.getTaps(), totalG);
    tapStrength = totalG;
    didTap = true;
    tap(1.0);
  }

  if (didTap) {
    addChaser();
    didTap = false;
  } 

  lights.copyPixelsMax(dots);
  for(int i = 0; i < numChasers; i++) 
    chaser[i].update(ms);

  paintMe.copyPixels(lights);
  lights.fade(ms);
  dots.fade(ms);
}





