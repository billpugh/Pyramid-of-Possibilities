// All libraries used in any other file need to be included here

#include "OctoWS2811.h"
#include "Adafruit_NeoPixel.h"
#include "Accelerometer.h"
#include "RNLights.h"
#include "RNLightsOctoWS2811.h"
#include "RNChaser.h"
#include "RNInfo.h"
#include "hsv2rgb.h"
#include "Controller.h"
#include "RNSerial.h"
#include <malloc.h>

#define FULL_STRIP 1

#if FULL_STRIP
#define LEDs 221
#define FIRST_LED 15
#define LAST_LED 235
#else
#define LEDs 60 
#define FIRST_LED 0
#define LAST_LED 59
#endif


const int ledsPerStrip = LAST_LED+1;

RNInfo info(ledsPerStrip, 0,0,0,0,0,0);
DMAMEM uint8_t displayMemory[ledsPerStrip*24];
uint8_t drawingMemory[ledsPerStrip*24];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory);

RNLightsOctoWS2811 lights(leds, drawingMemory, FIRST_LED);

static int heapSize(){
  return mallinfo().uordblks;
}

const int ONBOARD_LED_PIN = 13;
void setup() {
  leds.begin();
  leds.show();


  pinMode(ONBOARD_LED_PIN, OUTPUT); 
  for(int i = 0; i < 5; i++) {
    digitalWrite(ONBOARD_LED_PIN, HIGH);
    delay(700);
    digitalWrite(ONBOARD_LED_PIN, LOW);
    delay(300);
  }
  
  Serial.begin(115200);
  Serial.println("Started");
  Serial.println(leds.numPixels());
  Serial.println(lights.getNumPixels());
  initializeAccelerometer();
  setupSerial2(9600);
}

unsigned long avgTime = 0;
int count = 0;
void loop() {
  unsigned long startMicros = micros();
  updateAccelerometer();
  lights.reset();

  controllerPaint(lights);

  uint8_t avgPixelBrightness = lights.getAvgPixelBrightness();
  int avgBrightness = avgPixelBrightness * lights.getBrightness()/256;
  if (avgBrightness > 96) {
   
    int goal= 48+avgBrightness/2;
    if (goal > 160)
      goal = 160;

    int newBrightness = goal * 255 / avgPixelBrightness;
    info.printf("Avg brightness is %d/%d, goal is %d, Reducing brightness from %d -> %d\n",
      avgPixelBrightness, avgBrightness, goal, lights.getBrightness(), newBrightness);
    lights.setBrightness(newBrightness);
  }
 //  else info.printf("Avg brightness is %d/%d\n", avgPixelBrightness, avgBrightness);
    


  lights.show();
  unsigned long endMicros = micros();
  avgTime = (15*avgTime + endMicros - startMicros)/16;
  
  int timeToDelay = (10 - (endMicros - startMicros)/1000);
  if (timeToDelay > 0)
    delay(timeToDelay);
  if (count++ >= 100) {
    info.printf("Avg time = %5d, delay = %dms, heapSize = %d\n",
    avgTime, timeToDelay, heapSize());
    count = 0;
  }
  // Serial.println(millis()/10);
}



