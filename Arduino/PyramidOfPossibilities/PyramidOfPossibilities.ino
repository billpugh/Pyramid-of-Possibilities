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
const int LEDs = 220;
const int FIRST_LED = 15;

#else
const int LEDs = 60;
const int FIRST_LED = 0;

#endif

const int LAST_LED = FIRST_LED+LEDs-1;

const int ledsPerStrip = LAST_LED+1;

RNInfo info(LEDs, 0,0,0,0,0,0);
RNController controller(info);
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

  Serial.println(lights.getNumPixels());

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
const uint8_t chunk = 16;
uint8_t scaleBrightness(uint8_t value) {
  uint8_t result = 0;
  while (value > chunk) {
    result += chunk;
    value -= chunk;
    value/= 2;
  }
  return result + value;

}

unsigned long avgTime = 0;
int count = 0;
void loop() {
  unsigned long startMicros = micros();
  updateAccelerometer();
  lights.reset();

  controller.paint(lights);

  uint8_t avgPixelBrightness = lights.getAvgPixelBrightness();
  uint8_t avgBrightness = avgPixelBrightness * lights.getBrightness()/256;
  if (avgBrightness > 16) {

    int goal= scaleBrightness(avgBrightness);
    
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
  int blink = (millis() /100)%2;
  digitalWrite(ONBOARD_LED_PIN, blink);
  if (count++ >= 100) {
    info.printf("Avg time = %5d, delay = %dms, heapSize = %d\n",
    avgTime, timeToDelay, heapSize());
    count = 0;
  }
  // Serial.println(millis()/10);
}





