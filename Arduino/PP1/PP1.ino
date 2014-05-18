#include <Adafruit_NeoPixel.h>
#include <OctoWS2811.h>
#include "Accelerometer.h"
#include "RNLightsNeoPixel.h"
#include "RNChaser.h"
#include <hsv2rgb.h>


#define PIN 2

#define FULL_STRIP 1

#if FULL_STRIP
#define LEDs 221
#define FIRST_LED 10
#define LAST_LED 230
#else
#define LEDs 60 
#define FIRST_LED 0
#define LAST_LED 59
#endif

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LAST_LED+1, 2, NEO_GRB + NEO_KHZ800);

RNLightsNeoPixel lights = RNLightsNeoPixel(strip, FIRST_LED);

RNLights dots = RNLights(LEDs);

const uint8_t numChasers = 12;
RNChaser chaser[24] = { 
  RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),
  RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),
  RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),
  RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights)
  };

  static CHSV hsv;
static CRGB rgb;


unsigned long nextUpdate;
unsigned long nextChaser = 0;
long jiggles;
long taps;
long updates;
float totalJiggle;

bool didTap = false;
float tapStrength;

void p(char *fmt, ... ){
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  Serial.print(tmp);
}

uint8_t currentHue() {
  return (millis() / 100) % 256;
}
void setRandomPixel(float v) {
  hsv.v = 100*v+50;
  hsv.s = 255;
  hsv.h = currentHue();
  hsv2rgb_rainbow(hsv,rgb);
  int pixel = random(lights.getNumPixels());
  dots.setPixelColorMax(pixel, rgb.r, rgb.g, rgb.b);
}

void addChaser() {
  p("addChaser\n");
  if (nextChaser > millis())  return;

  uint16_t v = 50+tapStrength*200+random(50);
  if (v > 255)
    v = 255;
  p("Chaser v %d\n", v);
  nextChaser = millis() + 300;
  int c = random(numChasers);
  if (!chaser[c].active) {
    p("Activating chaser %d\n", c);
    if (tapStrength < 0.2 && random(4) != 1)
      chaser[c].hsv.h = currentHue();
    else 
      chaser[c].hsv.h = random(256);
    chaser[c].hsv.s  = 255;
    chaser[c].brightness = v;


    int rpm;
    if (tapStrength > 0.5 && random(6) == 0)
      rpm = 100 + random(60);
    else
      rpm = 20 + random(80);

    chaser[c].setRPM(rpm);

    chaser[c].activate(millis());

    p("%3d %4d  ", rpm, chaser[c].delay);
    p("%3d %3d %3d  %f\n", chaser[c].hsv.h,chaser[c].hsv.s, chaser[c].hsv.v, chaser[c].fadeValue);
    chaser[c].position = random(lights.getNumPixels());
    chaser[c].forward = random(3) != 0;
  } 
  else {
    p("chaser %d already active\n", c);
  }

}

void tap(float v) {
  if (v >= 1.0) {
    v = 0.5;
    didTap = true;
    taps++;
  } 
  else {
    jiggles ++;
    totalJiggle += v;
  }
  int num = v*LEDs/5;
  if (num < 1)
    num = 1;
  for(int i = 0; i < num; i++) {
    setRandomPixel(v);
  }
}


void updateTemperature() {

  if (didTap) {
    addChaser();
    didTap = false;
  } 
  else {
  }
}


void tapHandler(float f)
{
  byte source = readRegister(0x22);  // Reads the PULSE_SRC register
  p("Saw tap %f\n", f);
  tapStrength = f;
  tap(1.0);
}

void setup()
{
  delay(1000);
  Serial.begin(115200);
  Serial.println("Hello");
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH); 
  delay(2000);
  lights.show();
  initializeAccelerometer();
  Serial.println("Ready");
  digitalWrite(13, LOW); 
  for(int i = 0; i < numChasers; i++) 
    chaser[i].active = false;
  unsigned long ms = millis();
  lights.setLinearFade(ms, 100);
  dots.setFade(ms, 1000);
}

void accelerometerCallback( float totalG, 
float directionalG[3],
uint8_t source) {
  if (totalG > 0.01) {
    float num = totalG*5+0.1;
    if (num >= 1)
      num = 0.99; 
    tap(num);
    //      //      p("G %4f %4f %4f %4f\n", totalDiff, accelG[0], accelG[1], accelG[1]);
  }
  if (source != 0)
    tapHandler(totalG);
}

int count = 0;
void loop() {
  updateAccelerometer();
  updateTemperature();
  unsigned long ms = millis();

  lights.copyPixelsMax(dots);
  for(int i = 0; i < numChasers; i++) 
    chaser[i].update(ms);


  if (random(5) == 0)
    setRandomPixel(0.1);
  else if (random(10) == 0)
    setRandomPixel(0.3);
  else if (random(400) == 0) {
    tapStrength = 0.0;
    addChaser();
  }
  lights.show();
  lights.fade(ms);
  dots.fade(ms);
  count++;
  delay(5);

}






