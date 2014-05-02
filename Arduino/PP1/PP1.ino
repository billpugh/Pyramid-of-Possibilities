#include <Adafruit_NeoPixel.h>
#include <OctoWS2811.h>
#include "Accelerometer.h"
#include "RNLightsNeoPixel.h"
#include "RNChaser.h"
#include <hsv2rgb.h>


#define PIN 2

#define FULL_STRIP 0

#if FULL_STRIP
#define LEDs 219
#define FIRST_LED 10
#define LAST_LED 228
#else
#define LEDs 60 
#define FIRST_LED 0
#define LAST_LED 59
#endif

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LAST_LED+1, 2, NEO_GRB + NEO_KHZ800);

RNLightsNeoPixel lights = RNLightsNeoPixel(strip, FIRST_LED);

const uint8_t numChasers = 24;
RNChaser chaser[numChasers] = { 
  RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),
  RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),
  RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights),
  RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights), RNChaser(lights)
};


static CHSV hsv;
static CRGB rgb;

float temperature = 0.0;
unsigned long nextUpdate;
unsigned long nextChaser = 0;
long jiggles;
long taps;
long updates;
float totalJiggle;

bool didTap = false;

void p(char *fmt, ... ){
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  Serial.print(tmp);
}

void setRGB(float h, float v) {
  if (h > 1.0f)
    h = 1.0f;
  hsv.h = 230 * h;
  if (v > 1.0f)
    v = 1.0f;
  hsv.v = 110 + 140*v;
  hsv.s = 200;
  //  p("%3d %3d %3d ", hsv.h,hsv.s, hsv.v);
  hsv2rgb_rainbow(hsv,rgb);
  //  p("%3d %3d %3d\n", rgb.r, rgb.g, rgb.b);
}
void setRandomPixel(float v) {
  //  p("%f ", temperature);
  setRGB(temperature, v);
  int pixel = random(lights.getNumPixels());
  lights.setPixelColorMin(pixel, rgb.r, rgb.g, rgb.b);
}

void addChaser() {
  if (nextChaser > millis())  return;
  nextChaser = millis() + 300;
  setRGB(random(100)/100.0f, 1.0);
  int c = random(numChasers);
  if (!chaser[c].active) {
    chaser[c].activate();
    chaser[c].hsv.h = random(256);
    chaser[c].nextUpdate = millis();

    int rpm;
    if (random(3) == 0)
      rpm = 100 + random(100);
    else
      rpm = 20 + random(80);
     
    chaser[c].setRPM(rpm);

    p("%3d %4d  ", rpm, chaser[c].delay);
    p("%3d %3d %3d ", hsv.h,hsv.s, hsv.v);
    p("%3d %3d %3d\n", rgb.r, rgb.g, rgb.b);
    chaser[c].position = random(lights.getNumPixels());
    chaser[c].forward = random(3) != 0;
  } 
  else
    chaser[c].fade(10);
  
}

void tap(float v) {
  if (v >= 1.0) {
    v = 1.0;
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
  temperature = temperature*0.99;
  if (temperature < 0)
    temperature = 0;
  if (didTap) {
    temperature = temperature+0.1;
    p("Did tap %f\n", temperature);
    addChaser();
    didTap = false;
  } 
  else {
    //    temperature = temperature + jiggles/1000.0;
  }
}


void tapHandler()
{
  byte source = readRegister(0x22);  // Reads the PULSE_SRC register
  p("Saw tap\n");
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
}

void loop() {
  if (digitalRead(int1Pin)==1)  // Interrupt pin, should probably attach to interrupt function
  {
    float accelG[3]; 
    readAccelData(accelG);  // Read the x/y/z adc values

    float totalDiff = 0.0;
    for (int i=0; i<3; i++) {
      totalDiff += abs(accelG[i]);
    }

    if (totalDiff > 0.01) {
      tap(totalDiff/5+0.1);
      //      p("G %4f %4f %4f %4f\n", totalDiff, accelG[0], accelG[1], accelG[1]);
    }
  }

  if (digitalRead(int2Pin)==1)
  { 
    byte source;
    source = readRegister(0x0C);  // Read the interrupt source reg.
    if ((source & 0x08))  // If tap register is set go check that
      tapHandler();
  }
  updateTemperature();
  unsigned long ms = millis();
  for(int i = 0; i < numChasers; i++) {
    if (chaser[i].update(ms) && random(1000) < chaser[i].getRPM())
      chaser[i].fade(1);

  }
  if (random(30) == 0)
    setRandomPixel(0.1);
  lights.show();
  lights.fadeMultiply(245);
  delay(1);

}




