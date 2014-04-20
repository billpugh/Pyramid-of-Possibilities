#include <Adafruit_NeoPixel.h>
#include <hsv2rgb.h>
#include "RNLightsNeoPixel.h"
#include "RNChaser.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(240, 2, NEO_GRB + NEO_KHZ800);

RNLightsNeoPixel lights =  RNLightsNeoPixel(strip);

const uint8_t numChasers = 6;
RNChaser chaser[numChasers] = { 
  RNChaser(lights), 
  RNChaser(lights), 
  RNChaser(lights), 
  RNChaser(lights), 
  RNChaser(lights), 
  RNChaser(lights)};



void p(char *fmt, ... ){
  char tmp[256]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 256, fmt, args);
  va_end (args);
  Serial.print(tmp);
}

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
  chaser[0].active = true;
  chaser[0].lastUpdate = millis();
  chaser[0].setRPM(50);
  chaser[0].r = 120;

  chaser[1].active = true;
  chaser[1].lastUpdate = millis();
  chaser[1].position = 20;
  chaser[1].setRPM( 51);
  chaser[1].g = 120;
  chaser[2].active = true;
  chaser[2].lastUpdate = millis();
  chaser[2].forward = false;
  chaser[2].setRPM(100);
  chaser[2].b = 70;

}

void loop() {
  lights.fadeMultiply(240);
  unsigned long ms = millis();
  for(int i = 0; i < numChasers; i++) 
    chaser[i].update( ms);
  lights.show();
  delay(5);
}















