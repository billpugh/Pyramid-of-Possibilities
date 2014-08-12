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
#include <EEPROM.h>
#include <malloc.h>


// the setup() and loop() methods are in Main.cpp
// No actual code should go here, since Xcode/clang won't check it.


const int LAST_LED = constants.FIRST_LED+constants.LEDs-1;
const int ledsPerStrip = LAST_LED+1;

DMAMEM uint8_t displayMemory[240*24];
uint8_t drawingMemory[240*24];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory);

RNLightsOctoWS2811 octoLights(leds, drawingMemory, constants.FIRST_LED);

RNLights *lights = &octoLights;

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
    setupMain();
}
