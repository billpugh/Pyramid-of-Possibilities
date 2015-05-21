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
#include "StripLighting.h"


//OctoWS2811 allocation:
//
//Channel 0:  Starburts on left playfield, 29 pixels each, order is: Highest first, middle, lowest last
//Channel 1: Starbursts on right playfield, same order
//Channel 2: LED strip on left inside playfield, starting from bottom and going up
//Channel 3: LED strip on right inside play field, starting from bottom and going up
//Channel 4: Score digits followed by Time digits (exactly in diagram I supplied earlier)
//Channels 5-7: unused for PDF
//
//
//MCP23017 allocation:
//GPA0: Left high pocket
//GPA1: Left middle pocket
//GPA2: Left low pocket
//GPA3: Right high pocket
//GPA4: Right middle pocket
//GPA5: Right low pocket
//
//GPB3: Loud bell (active high)
//GPB2: Chime (active high)


PachinkoState pachinkoState = e_Boot;


static const uint16_t endGameBellOffPeriod = 400;
static const uint16_t endGameBellOnPeriod = 200;
static const uint16_t endGameBellRings = 5;

static const uint16_t gameDuration = 180;

static const uint16_t endGameLightsOut = 600;
static const uint32_t endGameDuration = 18000;
static const uint32_t LEDsPerStrip = 300;


static const uint32_t STRIP_0 = 0;
static const uint32_t STRIP_1 = 1 * LEDsPerStrip;
static const uint32_t STRIP_2 = 2 * LEDsPerStrip;

static const uint32_t STRIP_3 = 3 * LEDsPerStrip;
static const uint32_t STRIP_4 = 4 * LEDsPerStrip;

DMAMEM int displayMemory[LEDsPerStrip * 6];
int drawingMemory[LEDsPerStrip * 6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(LEDsPerStrip, displayMemory, drawingMemory, config);


RNDigit time0(leds, STRIP_4, 5,  13);
RNDigit time1(leds, time0.nextPixel());
RNDigit time2(leds, time1.nextPixel());
RNNumberDisplay timeDisplay(time0, time1, time2);

RNDigit score0(leds, time2.nextPixel());
RNDigit score1(leds, score0.nextPixel());
RNDigit score2(leds, score1.nextPixel());
RNDigit score3(leds, score2.nextPixel());
RNNumberDisplay scoreDisplay(score0, score1, score2, score3);

Adafruit_MCP23017 io;

Pocket  LH(leds, STRIP_1 + 0 * Pocket::LEDS_PER_POCKET, io, 0);
Pocket  LM(leds, STRIP_1 + 1 * Pocket::LEDS_PER_POCKET, io, 1);
Pocket  LL(leds, STRIP_1 + 2 * Pocket::LEDS_PER_POCKET, io, 2);
Pocket  RH(leds, STRIP_0 + 0 * Pocket::LEDS_PER_POCKET, io, 3);
Pocket  RM(leds, STRIP_0 + 1 * Pocket::LEDS_PER_POCKET, io, 4);
Pocket  RL(leds, STRIP_0 + 2 * Pocket::LEDS_PER_POCKET, io, 5);


Bell GameOverBell(io, 11, endGameBellOnPeriod, endGameBellOffPeriod);
Bell scoreBell(io, 10, 100, 100);

StripLighting leftStrip(leds, STRIP_2, 120);
StripLighting rightStrip(leds, STRIP_3, 120);

uint32_t gameStarted;
uint32_t gameEnds;
uint32_t now;
uint16_t score;


void switchToIdleMode() {
    score = 0;
    pachinkoState = e_Attract;
    GameOverBell.ring(1);
    scoreBell.ring(1);
    
    timeDisplay.setColor(0x00ff00);
    scoreDisplay.setColor(0x00ff00);
    scoreDisplay.setValue(0);
    timeDisplay.setValue(gameDuration);
    
}

void endGame() {
    GameOverBell.ring(endGameBellRings);
    pachinkoState = e_GameOver;
    timeDisplay.setColor(0xffffff);
    scoreDisplay.setColor(0xffffff);
    timeDisplay.setValue(0);
    scoreDisplay.setValue(score);
    
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
        Serial.println("Game starting");
        pachinkoState = e_GameInProgress;
        gameStarted = now;
        gameEnds = now + gameDuration * 1000;
        GameOverBell.ring();
        score = 0;
    }
    int multiplier = 1;
    int secondsRemaining = (gameEnds - millis()) / 1000;
    if (secondsRemaining < 10)
        multiplier = 3;
    else if (secondsRemaining < 30)
        multiplier = 2;
    score += points * multiplier;
    scoreDisplay.setValue(score);
    scoreBell.ring(points);
}

void setupMain() {
    leds.begin();
    leds.show();
    digitalWrite(13, LOW);
    delay(1000);
    digitalWrite(13, HIGH);
    delay(1000);
    digitalWrite(13, LOW);
    Serial.begin(9600);
    Serial.println("Hello");
    io.begin();
    
    LH.begin();
    LM.begin();
    LL.begin();
    RH.begin();
    RM.begin();
    RL.begin();
    GameOverBell.begin();
    scoreBell.begin();
    leftStrip.fill();
    rightStrip.fill();
    scoreDisplay.setValue(0);
    timeDisplay.setValue(0);
    timeDisplay.clear();
    scoreDisplay.clear();
    
    Serial.println("Setup complete");
    if (0) {
        //    GameOverBell.ring(4);
        //    for(int i = 0; i < 1000; i++) {
        //      GameOverBell.update();
        //      delay(10);
        //    }
        scoreBell.ring(5);
        
        Serial.println("Bell rung");
        
        for (int i = 180; i >= 0; i--) {
            timeDisplay.setValue(i);
            scoreBell.update();
            leds.show();
            delay(50);
        }
        
        for (int i = 9999; i >= 0; i--) {
            scoreDisplay.setValue(i);
            leds.show();
            delay(10);
        }
    }
    
    
    if (0) {
        LH.gameOver();
        LM.gameOver();
        LL.gameOver();
        leds.show();
        delay(1000);
        LH.startTest();
        LM.startTest();
        LL.startTest();
        Serial.print(LH.rgb);
        Serial.print(", ");
        Serial.print(LH.strip);
        Serial.print(", ");
        Serial.println(LH.pos);
        leds.show();
        delay(100);
        while (LH.updateTest()) {
            LM.updateTest();
            LL.updateTest();
            Serial.print(LH.strip);
            Serial.print(", ");
            Serial.println(LH.pos);
            leds.show();
            delay(100);
        }
    }
    switchToIdleMode();
    
    Serial.println("Game starting");
}

int scoreMultiplier() {
    if (pachinkoState != e_GameInProgress)
        return 1;
    int secondsRemaining = (gameEnds - now) / 1000;
    if (secondsRemaining < 10)
        return 3;
    if (secondsRemaining < 30)
        return 2;
    return 1;
    
}

int stripCount = 0;
void loopMain() {
    now = millis();
    checkPockets();
    if (stripCount++ == 5) {
        stripCount = 0;
        leftStrip.rotate();
        rightStrip.rotate();
    }
    int secondsRemaining = (gameEnds - now) / 1000;
    if (secondsRemaining < 0)
        secondsRemaining = 0;
    
    
    switch (pachinkoState) {
        case e_Boot:
        case e_Attract:
            break;
            
        case  e_GameInProgress:
            if (secondsRemaining < 10)
                timeDisplay.setColor(0xff4040);
            else if (secondsRemaining < 30)
                timeDisplay.setColor(0xffff00);
            timeDisplay.setValue(secondsRemaining);
            
            if (now > gameEnds)
                endGame();
            
            break;
            
        case e_GameOver:
            timeDisplay.setValue( (now - gameEnds) / 100);
            if (now > gameEnds + endGameDuration)
                switchToIdleMode();
            break;
    }
    GameOverBell.update();
    scoreBell.update();
    leds.show();
    delay(20);
}

