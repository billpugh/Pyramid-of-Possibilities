// All libraries used in any other file need to be included here

#include "Constants.h"

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
#include <EEPROM.h>
#include <malloc.h>


const int LAST_LED = constants.FIRST_LED+constants.LEDs-1;
const int ledsPerStrip = LAST_LED+1;

DMAMEM uint8_t displayMemory[240*24];
uint8_t drawingMemory[240*24];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory);

RNLightsOctoWS2811 lights(leds, drawingMemory, constants.FIRST_LED);

//Platform platform( 0,0,0,0,700,0);
//RNInfo info(LEDs, platform);
//RNController controller(info);

RNInfo *info;
RNController * controller;


static int heapSize(){
  return mallinfo().uordblks;
}

const int ONBOARD_LED_PIN = 13;
void setup() {
  
  leds.begin();
  leds.show();
  Serial.begin(115200);
  Serial.println("Started");

  pinMode(ONBOARD_LED_PIN, OUTPUT); 
  for(int i = 0; i < 5; i++) {
    digitalWrite(ONBOARD_LED_PIN, HIGH);
    delay(700);
    digitalWrite(ONBOARD_LED_PIN, LOW);
    delay(300);
  }


  Serial.println(leds.numPixels());
  Serial.println(lights.getNumPixels());
  initializeAccelerometer(constants.PULSE_THSX,constants.PULSE_THSY,
        constants.PULSE_THSZ);
  setupSerial2(9600);
  Platform platform( 0,0,0,0,1200,0);
  info = new RNInfo(constants.LEDs, platform);
  controller = new RNController(*info);
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

void accelerometerCallback( float totalG, float directionalG[3], uint8_t source)  {
   info->accelerometerCallback(totalG,directionalG, source);
}

void capOverallBrightness(RNLights & lights) {
 uint8_t avgPixelBrightness = lights.getAvgPixelBrightness();
  uint8_t avgBrightness = avgPixelBrightness * lights.getBrightness()/256;
  if (avgBrightness > 16) {

    int goal= scaleBrightness(avgBrightness);
    
    int newBrightness = goal * 255 / avgPixelBrightness;
    info->printf("Avg brightness is %d/%d, goal is %d, Reducing brightness from %d -> %d\n",
    avgPixelBrightness, avgBrightness, goal, lights.getBrightness(), newBrightness);
    lights.setBrightness(newBrightness);
  }
  //  else info.printf("Avg brightness is %d/%d\n", avgPixelBrightness, avgBrightness);

}


Platform platform( 0,0,0,0,700,0);


void loop() {
  unsigned long startMicros = micros();

  updateAccelerometer();
  
  // display lights
  lights.reset();
  controller->paint(lights);
  capOverallBrightness(lights);
  lights.show();
  

  unsigned long endMicros = micros();
  avgTime = (15*avgTime + endMicros - startMicros)/16;

  int timeToDelay = (10 - (endMicros - startMicros)/1000);
  if (timeToDelay > 0)
    delay(timeToDelay);
  int blink = (millis() /100)%2;
  digitalWrite(ONBOARD_LED_PIN, blink);
  if (count++ >= 100) {
    info->printf("Avg time = %5d, delay = %dms, heapSize = %d\n",
    avgTime, timeToDelay, heapSize());
    count = 0;
  }
  // Serial.println(millis()/10);
}





