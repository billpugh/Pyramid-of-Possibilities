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
#include "ledPositions.h"
#include "mac.h"
#include "watchdog.h"
#include "RNEEPROM.h"
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


  pinMode(ONBOARD_LED_PIN, OUTPUT); 
  for(int i = 0; i < 5; i++) {
    digitalWrite(ONBOARD_LED_PIN, HIGH);
    delay(700);
    digitalWrite(ONBOARD_LED_PIN, LOW);
    delay(300);
  }

  Serial.println("PoP board starting");
  print_mac();
  char  platformData[9];
  Platform platform(0,-200,0,500,0);
  bool success = readFromEEPROM(sizeof(Platform), (char*) &platform);
  if (success) {
    Serial.print("Read from EEPROM ");
    Serial.print(platform.identifier);
    Serial.println();
  }
  int bytesRead = Serial.readBytes(platformData, 9);
  Serial.print(bytesRead);
  Serial.println(" bytes read");
  Serial.print(sizeof(Platform));
  Serial.println(" platform size");
  if (bytesRead == 9) {
    bool success = platform.initialize(platformData, 9);
    if (success) {
      writeToEEPROM(sizeof(Platform), (char*) &platform);
      Serial.println("success, wrote to EEPROM");
    }
    else
      Serial.println("Fail parsing data from central");
    Serial.print(platform.y);
  }
  initializeAccelerometer(constants.PULSE_THSX,constants.PULSE_THSY,
  constants.PULSE_THSZ);
  setupSerial2(57600);

  info = new RNInfo(constants.LEDs, platform);
  controller = new RNController(*info);

  info->printf("Running. id = %3d, xyz = %4d,%4d,%4d\n", info->identifier, info->x, info->y,info->z);
  info->printf("%-3s  %-4s %-4s %-11s    %-4s %-4s   %-11s  %-11s\n",
  "id", "x", "y", "angle", "g x", "g y", "angle", "radius");
  int minAngleLED = 0;
  int maxAngleLED = 0;
  float maxAngle = 0;
  float minAngle =1;
  int closestLED = 0;
  float closestLEDRange = 100000;
  for(int i = 0; i < info->numLEDs; i++)  {
    info->printf("%3d  %4d %4d %11f    %4d %4d   %11f  %11f, %11f\n",
    i, getLEDXPosition(i),
    getLEDYPosition(i), 
    info->getLocalAngle(i)*360,
    info->x + getLEDXPosition(i),
    info->y + getLEDYPosition(i), 
    info->getGlobalAngle(i)*360,
    (info->getGlobalAngle(i) - info->getPlatformGlobalAngle())*360,
    info->getGlobalRadius(i));
    float angleDiff = info->getGlobalAngle(i) - info->getPlatformGlobalAngle();
    angleDiff = angleDiff  - round(angleDiff);

    if (maxAngle < angleDiff) {
      maxAngle = angleDiff;
      maxAngleLED = i;
    }
    if (minAngle > angleDiff) {
      minAngle = angleDiff;
      minAngleLED = i;
    }
    if (closestLEDRange > info->getGlobalRadius(i)) {
      closestLEDRange =info->getGlobalRadius(i);
      closestLED = i;
    }

  }

  lights.setAllPixelColors(0, 20, 0);
  lights.setPixelColor(minAngleLED, 255, 0, 0);
  lights.setPixelColor(maxAngleLED, 0, 0, 255);
  lights.setPixelColor(closestLED, 80,80,80);

  info->printf("minimum led %3d at %11f\n", minAngleLED, minAngle*360);
  info->printf("closest led %3d at %11f\n", closestLED, closestLEDRange*360);
  info->printf("maximum led %3d at %11f\n", maxAngleLED, maxAngle*360);

  lights.show();
  delay(10000);
  lights.reset();
  
  createWatchdog(100000);


}

const uint8_t chunk = constants.brightnessChunkSize;
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
    
#ifdef RN_PRINT_BRIGHTNESS_ADJUSTMENTS
    info->printf("Avg brightness is %d/%d, goal is %d, Reducing brightness from %d -> %d\n",
    avgPixelBrightness, avgBrightness, goal, lights.getBrightness(), newBrightness);
#endif /* RN_PRINT_BRIGHTNESS_ADJUSTMENTS */

    lights.setBrightness(newBrightness);
  }
  //  else info.printf("Avg brightness is %d/%d\n", avgPixelBrightness, avgBrightness);

}


Platform platform( 0,0,0,700,0);


void loop() {
  refreshWatchdog();
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

  // Print head size for debugging.
#ifdef RN_PRINT_HEAP_SIZE
    info->printf("Avg time = %5d, delay = %dms, heapSize = %d\n",
    avgTime, timeToDelay, heapSize());
    count = 0;
#endif /* RN_PRINT_HEAP_SIZE */

  }
  // Serial.println(millis()/10);
}







