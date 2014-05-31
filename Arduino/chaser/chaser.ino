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

void p(char *fmt, ... ){
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  Serial.print(tmp);
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);

  Serial.println("Starting");
  lights.show();
  lights.setFade(millis(), 250);
  for(int i = 0; i < numChasers; i++) {
    chaser[i].active = true;
    chaser[i].setRPM(50 + random(50));
    if (random(2) == 0)
      chaser[i].forward = false;
    chaser[i].hsv.h = random(255);
  }
//  p("Fade %f\n", lights.logFade);
}

void loop() {

  unsigned long ms = millis();
  int amount = lights.fade(ms);
  
  p("%d %d\n", ms, amount);
  for(int i = 0; i < numChasers; i++) {
    if (!chaser[i].update(ms)) {
      chaser[i].setRPM(20 + random(70));
      chaser[i].activate(ms);
    }

  }
  lights.show();
  delay(50);
}
















