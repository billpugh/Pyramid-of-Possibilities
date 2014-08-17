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
#include "easing.h"
#include "watchdog.h"
#include "RNEEPROM.h"
#include "PopMain.h"
#include "TimerThree.h"
#include "UploadParameters.h"
#include "UploadConstants.h"
#include <EEPROM.h>
#include <malloc.h>

// the setup() and loop() methods are in Main.cpp
// As little code as possible should go here, since Xcode/clang won't check it.

DMAMEM uint8_t displayMemory[240*24];
uint8_t drawingMemory[240*24];

const int LAST_LED = constants.FIRST_LED+constants.LEDs-1;
const int ledsPerStrip = LAST_LED+1;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory);

RNLightsOctoWS2811 oLights(leds, drawingMemory, constants.FIRST_LED);

RNLights *lights;

void initializeConstantsFromEEPROM() {
}

void initializeLEDs() {
  leds.begin();
  leds.show();
  lights = & oLights;

}
enum Action {
  runPlatform, uploadParameters, uploadConstants};

const Action action = runPlatform;
void setup() {

    Serial.begin(constants.usbSerialBaudRate);

    pinMode(ONBOARD_LED_PIN, OUTPUT);
    for(int i = 0; i < 10; i++) {
      digitalWrite(ONBOARD_LED_PIN, HIGH);
      delay(700);
      digitalWrite(ONBOARD_LED_PIN, LOW);
      delay(300);
    }

  switch(action) {
  case runPlatform:
    initializeConstantsFromEEPROM();
    initializeLEDs();

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

