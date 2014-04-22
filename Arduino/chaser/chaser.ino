#include <Adafruit_NeoPixel.h>
#include <hsv2rgb.h>
#include "RNLightsNeoPixel.h"
#include "RNChaser.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, 2, NEO_GRB + NEO_KHZ800);

RNLightsNeoPixel lights =  RNLightsNeoPixel(strip);

const uint8_t numChasers = 6;
RNChaser chaser[numChasers] = { 
  RNChaser(lights), 
  RNChaser(lights), 
  RNChaser(lights), 
  RNChaser(lights), 
  RNChaser(lights), 
  RNChaser(lights)};



CHSV hsv;
CRGB rgb;


float easeInOutQuad(float t) {
  t = t*2;
  if (t < 1)
    return t*t/2;
  t -= 2;
  return 1-t*t/2;
}

float easeInOutCubic(float t) {
  t = t*2;
  if (t < 1)
    return t*t*t/2;
  t -= 2;
  return 1+t*t*t/2;
}


void setup() {
  delay(1000);
  Serial.begin(115200);
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);

  Serial.println("Starting");
  lights.show();
  for(int i = 0; i < numChasers; i++) {
    chaser[i].active = true;
    chaser[i].setRPM(50 + random(50));
    if (random(2) == 0)
      chaser[i].forward = false;
    chaser[i].r = chaser[i].g = chaser[i].b = 0;
    switch (random(3)) {
    case 0:
      chaser[i].r = 70 + random(50);
      break;
    case 1:
      chaser[i].g = 70 + random(50);
      break;
    case 2:
      chaser[i].b = 70 + random(50);
      break;
    }
  }



}

void loop() {
  lights.fadeMultiply(240);
  unsigned long ms = millis();
  for(int i = 0; i < numChasers; i++) {
    chaser[i].update( ms);

  }
  lights.show();
  delay(5);
}
















