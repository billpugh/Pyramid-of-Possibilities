//
//  PachinkoMain.cpp
//  PachinkoCode
//
//  Created by Bill on 4/23/15.
//
//

#include "PachinkoMain.h"

#include "Arduino.h"
#include "OctoWS2811.h"
#include "Adafruit_MCP23017.h"
#include "Pocket.h"
#include "RNDigit.h"
#include "RNNumberDisplay.h"


PachinkoState pachinkoState = e_Boot;

static const uint16_t LOUD_BELL_PIN = 600;

static const uint16_t endGameBellPeriod = 600;
static const uint16_t endGameBellOnPeriod = 200;

static const uint16_t endGameBellRings = 5;

static const uint16_t endGameLightsOut = 600;
static const uint32_t endGameDuration = 20000;
static const uint32_t LEDsPerStrip = 300;


static const uint32_t STRIP_0 = 0;
static const uint32_t STRIP_1 = 1*LEDsPerStrip;
static const uint32_t STRIP_2 = 2*LEDsPerStrip;

static const uint32_t STRIP_3 = 3*LEDsPerStrip;
static const uint32_t STRIP_4 = 4*LEDsPerStrip;

DMAMEM int displayMemory[LEDsPerStrip*6];
int drawingMemory[LEDsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(LEDsPerStrip, displayMemory, drawingMemory, config);
Adafruit_MCP23017 io;

RNDigit score0(leds, 0*RNDigit::MAX_PIXELS);
RNDigit score1(leds, 1*RNDigit::MAX_PIXELS);
RNDigit score2(leds, 2*RNDigit::MAX_PIXELS);
RNDigit score3(leds, 3*RNDigit::MAX_PIXELS);
RNNumberDisplay scoreDisplay(score0, score1, score2, score3);

RNDigit time0(leds, 4*RNDigit::MAX_PIXELS, 13);
RNDigit time1(leds, 4*RNDigit::MAX_PIXELS+13);
RNDigit time2(leds, 5*RNDigit::MAX_PIXELS+13);
RNNumberDisplay timeDisplay(time0, time1, time2);


Pocket  LH(leds, STRIP_0+2*Pocket::LEDS_PER_POCKET, io, 0);
Pocket  LM(leds, STRIP_0+1*Pocket::LEDS_PER_POCKET, io, 1);
Pocket  LL(leds, STRIP_0+0*Pocket::LEDS_PER_POCKET, io, 2);
Pocket  RH(leds, STRIP_1+2*Pocket::LEDS_PER_POCKET, io, 3);
Pocket  RM(leds, STRIP_1+1*Pocket::LEDS_PER_POCKET, io, 4);
Pocket  RL(leds, STRIP_1+0*Pocket::LEDS_PER_POCKET, io, 5);


uint32_t gameStarted;
uint32_t gameEnds;
uint32_t now;

void setLoudBell(bool on) {}
void switchToIdleMode() {}
void setPlayfieldLights(bool on) {}
void endGame() {}
void playGame() {}


void setupMain() {
    io.begin();
    leds.begin();
    
}

void loopMain() {
    now = millis();
    
    switch(pachinkoState) {
        case e_Boot:
        case e_Attract:
        case  e_GameInProgress:
            if (now > gameEnds)
                endGame();
            else
                playGame();
            
        case e_GameOver:
            uint32_t afterGame = now - gameEnds;
            uint32_t bellCount = afterGame/endGameBellPeriod;
            
            setLoudBell(bellCount < endGameBellRings && afterGame % endGameBellPeriod < endGameBellOnPeriod );
            setPlayfieldLights(afterGame < endGameLightsOut);
            if (afterGame > endGameDuration)
                switchToIdleMode();
    }
}

