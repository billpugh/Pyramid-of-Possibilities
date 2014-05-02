#include <Adafruit_NeoPixel.h>
#include <OctoWS2811.h>
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
    chaser[i].hsv.h = random(255);
  }



}

void loop() {
  lights.fadeMultiply(240);
  unsigned long ms = millis();
  for(int i = 0; i < numChasers; i++) {
    if (!chaser[i].update( ms)) {
      chaser[i].activate();
      chaser[i].setRPM(20 + random(70));
    }

  }
  lights.show();
  delay(5);
}
















