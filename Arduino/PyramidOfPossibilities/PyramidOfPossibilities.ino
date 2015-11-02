// All libraries used in any other file need to be included here

#include "Constants.h"
#include "OctoWS2811.h"
#include "Adafruit_NeoPixel.h"
#include "Accelerometer.h"
#include "RNLights.h"
#include "RNGradient.h"
#include "RNLightsOctoWS2811.h"
#include "RNChaser.h"
#include "RNInfo.h"
#include "hsv2rgb.h"
#include "Controller.h"
#include "RNSerial.h"
#include "ledPositions.h"
#include "mac.h"
#include "easing.h"
#include "watchdog.h"
#include "RNEEPROM.h"
#include "PopMain.h"
#include "TimerThree.h"
#include "UploadParameters.h"
#include "UploadConstants.h"
#include <i2c_t3.h>
#include <EEPROM.h>
#include <malloc.h>

// the setup() and loop() methods are in Main.cpp
// As little code as possible should go here, since Xcode/clang won't check it.

DMAMEM uint8_t displayMemory[240*24];
uint8_t drawingMemory[240*24];



RNLights *lights;

void initializeConstantsFromEEPROM() {
}

void initializeLEDs() {
  const int LAST_LED = constants.FIRST_LED+constants.LEDs-1;
  const int ledsPerStrip = LAST_LED+1;

  OctoWS2811 *leds = new OctoWS2811(ledsPerStrip, displayMemory, drawingMemory);

  RNLightsOctoWS2811 *oLights
    = new RNLightsOctoWS2811(*leds, drawingMemory, constants.FIRST_LED);

  leds->begin();
  leds->show();
  lights = oLights;

}
enum Action {
  runPlatform, uploadParameters, uploadConstants};

const Action action = runPlatform;
void setup() {

  initializeConstantsFromEEPROM();
  Serial.begin(constants.usbSerialBaudRate);
  initializeLEDs();

  pinMode(ONBOARD_LED_PIN, OUTPUT);
#ifdef FULL_STRIP
  for(int i = 0; i < constants.initialDelay; i++) {
    digitalWrite(ONBOARD_LED_PIN, HIGH);
    delay(700);
    digitalWrite(ONBOARD_LED_PIN, LOW);
    delay(300);
  }
#endif

  switch(action) {
  case runPlatform:
    setupMain();
    break;
  case uploadParameters:
    setupUploadParameters();
    break;
  case uploadConstants:
    setupUploadConstants();
    break;
  }


}

void loop() {
  switch(action) {
  case runPlatform:
    loopMain();
    break;
  default:
    digitalWrite(ONBOARD_LED_PIN, HIGH);
    delay(350);
    digitalWrite(ONBOARD_LED_PIN, LOW);
    delay(150);
  }
}


