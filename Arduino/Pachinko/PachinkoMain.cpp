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

static const uint16_t endGameBellOffPeriod = 400;
static const uint16_t endGameBellOnPeriod = 200;
static const uint16_t endGameBellRings = 5;

static const uint16_t gameDuration = 180;

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


RNDigit time0(leds, 0, 13);
RNDigit time1(leds, time0.nextPixel());
RNDigit time2(leds, time1.nextPixel());
RNNumberDisplay timeDisplay(time0, time1, time2);


RNDigit score0(leds, time2.nextPixel());
RNDigit score1(leds, score0.nextPixel());
RNDigit score2(leds, score1.nextPixel());
RNDigit score3(leds, score2.nextPixel());
RNNumberDisplay scoreDisplay(score0, score1, score2, score3);

Adafruit_MCP23017 io;

Pocket  LH(leds, STRIP_0+2*Pocket::LEDS_PER_POCKET, io, 0);
Pocket  LM(leds, STRIP_0+1*Pocket::LEDS_PER_POCKET, io, 1);
Pocket  LL(leds, STRIP_0+0*Pocket::LEDS_PER_POCKET, io, 2);
Pocket  RH(leds, STRIP_1+2*Pocket::LEDS_PER_POCKET, io, 3);
Pocket  RM(leds, STRIP_1+1*Pocket::LEDS_PER_POCKET, io, 4);
Pocket  RL(leds, STRIP_1+0*Pocket::LEDS_PER_POCKET, io, 5);


Bell GameOverBell(io, 10, endGameBellOnPeriod, endGameBellOffPeriod);
Bell scoreBell(io, 11, 100, 100);

uint32_t gameStarted;
uint32_t gameEnds;
uint32_t now;
uint16_t score;


void switchToIdleMode() {
    score = 0;
    timeDisplay.setValue(gameDuration);
    scoreDisplay.setValue(0);
}

void endGame() {
    GameOverBell.ring(endGameBellRings);
    pachinkoState = e_GameOver;
}

void checkPockets() {
    LH.checkAndUpdate();
    LM.checkAndUpdate();
    LL.checkAndUpdate();
    RH.checkAndUpdate();
    RM.checkAndUpdate();
    RL.checkAndUpdate();
}

void scorePoints(int points) {
    if (pachinkoState == e_GameOver)
        return;
    
    if (pachinkoState == e_Attract) {
        // Start game
        pachinkoState = e_GameInProgress;
        gameStarted = now;
        gameEnds = now+endGameDuration;
        score = 0;
    }
    score += points;
    scoreDisplay.setValue(score);
    scoreBell.ring(points);
}

void setupMain() {
    io.begin();
    leds.begin();
    switchToIdleMode();
}

int scoreMultiplier() {
    if (pachinkoState !=e_GameInProgress)
        return 1;
    int secondsRemaining = (gameEnds - now)/1000;
    if (secondsRemaining < 10)
        return 3;
    if (secondsRemaining < 30)
        return 2;
    return 1;
    
}

void loopMain() {
    now = millis();
    checkPockets();
    int secondsRemaining = (gameEnds - now)/1000;
    
    switch(pachinkoState) {
        case e_Boot:
        case e_Attract:
            break;
            
        case  e_GameInProgress:
            if (secondsRemaining < 0) secondsRemaining=0;
            timeDisplay.setValue(secondsRemaining);
            
            timeDisplay.setValue(gameDuration);
            if (now > gameEnds)
                endGame();
            
            break;
            
        case e_GameOver:
            if (now > gameEnds + endGameDuration)
                switchToIdleMode();
            break;
    }
}

