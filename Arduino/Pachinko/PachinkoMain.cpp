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
#include "RemoteControl.h"
#include <EEPROM.h>


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
static const uint32_t endGameDurationNormal = 18000;
static const uint32_t endGameDurationEmcee = 5*60*1000;
static const uint32_t warningDuration = 2000;
static const uint32_t pauseDuration = 60*1000;


static const uint8_t start_RemoteEnabled = 20;

static const uint8_t numRemotes = 8;
static const uint32_t LEDsPerStrip = 300;


static const uint32_t STRIP_0 = 0;
static const uint32_t STRIP_1 = 1 * LEDsPerStrip;
static const uint32_t STRIP_2 = 2 * LEDsPerStrip;

static const uint32_t STRIP_3 = 3 * LEDsPerStrip;
static const uint32_t STRIP_4 = 4 * LEDsPerStrip;
static const uint8_t SIDE_STRIP_LENGTH = 121;

DMAMEM int displayMemory[LEDsPerStrip * 6];
int drawingMemory[LEDsPerStrip * 6];



const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(LEDsPerStrip, displayMemory, drawingMemory, config);


// red = 0
// yellow = 64
// green = 96
// cyan = 136
// blue = 160
// Magenta = 208

int AmbientColorHue[] = {
    0, 96, 160, 64, 208, 136, -1};

RNDigit time0(leds, STRIP_4, 5,  13);
RNDigit time1(leds, time0.nextPixel());
RNDigit time2(leds, time1.nextPixel());
RNNumberDisplay timeDisplay(time0, time1, time2);

RNDigit score0(leds, time2.nextPixel());
RNDigit score1(leds, score0.nextPixel());
RNDigit score2(leds, score1.nextPixel());
RNNumberDisplay scoreDisplay(score0, score1, score2);

Adafruit_MCP23017 io;

Pocket  LH(leds, STRIP_1 + 0 * Pocket::LEDS_PER_POCKET, io, 0, 1);
Pocket  LM(leds, STRIP_1 + 1 * Pocket::LEDS_PER_POCKET, io, 1, 2);
Pocket  LL(leds, STRIP_1 + 2 * Pocket::LEDS_PER_POCKET, io, 2, 3);
Pocket  RH(leds, STRIP_0 + 0 * Pocket::LEDS_PER_POCKET, io, 3, 1);
Pocket  RM(leds, STRIP_0 + 1 * Pocket::LEDS_PER_POCKET, io, 4, 2);
Pocket  RL(leds, STRIP_0 + 2 * Pocket::LEDS_PER_POCKET, io, 5, 3);


Bell GameOverBell(io, 11, endGameBellOnPeriod, endGameBellOffPeriod);
Bell scoreBell(io, 10, 100, 100);

const uint8_t AmbientPin = 9;

StripLighting leftStrip(leds, STRIP_2, SIDE_STRIP_LENGTH);
StripLighting rightStrip(leds, STRIP_3, SIDE_STRIP_LENGTH);

uint16_t numGames;
uint16_t sumAllScores;
uint16_t maxAllScores;
uint32_t gameStarted;
uint32_t gameEnds;
uint32_t now;
uint16_t score;
uint16_t lowPocketScore;
uint32_t warningStarted = 0;
bool showingWarning = false;
bool lowestPocketsDisabled = false;
bool emceeMode = false;
bool gamePaused = false;
uint32_t timeRemainingIfResumed;
uint32_t timePauseStarted;

AmbientMode currentAmbientMode;
AmbientColorChoice currentAmbientColorChoice = AmbientGreen;
AmbientPatternChoice currentAmbientPatternChoice;

int updateCount = 0;
bool remoteEnabled[16];

void showEnabledState() {
    Serial.println("Show enabled state");
     for(int pos = 0; pos < SIDE_STRIP_LENGTH; pos++)
         leds.setPixel(STRIP_3+pos, 0);
    for(int i = 0; i < numRemotes; i++) {
        int rgb = remoteEnabled[i] ? 0x00ff00 : 0xff0000;
        for(int pos = 0; pos < 8; pos++)
            leds.setPixel(STRIP_3+i*10+pos, rgb);
    }
    leds.show();
}

int randomColor2(int offset, bool vary) {
    CHSV hsv;
    if (currentAmbientMode == AmbientColor || !vary && currentAmbientMode == AmbientPattern
        && currentAmbientPatternChoice == AmbientSparkles) {
        if (vary)
            hsv.v = (randomByte() & 0x7f) + 96;
        else
            hsv.v = 255;

        if (currentAmbientColorChoice == AmbientWhite) {
            hsv.h = 0;
            hsv.s = 0;
        } else {
            hsv.h = AmbientColorHue[currentAmbientColorChoice];
            if(vary)
                hsv.s = (randomByte() & 0x3f)| 0xc0;
            else
                hsv.s = 255;
            
        }
    } else if (currentAmbientMode == AmbientPattern){
        switch (currentAmbientPatternChoice) {
            case AmbientRainbow:
                hsv.h = (3*(updateCount + offset)) & 0xff;
                hsv.s = 255;
                hsv.v = 250;
                break;
            case AmbientComets:
            case AmbientSparkles:
                switch (randomByte() & 0x0f) {
                        
                    case 0:
                        hsv.h = 0;
                        hsv.s = 0;
                        hsv.v = 250;
                        break;
                    case 1:
                    case 2:
                        hsv.h = AmbientColorHue[currentAmbientColorChoice];
                        hsv.s = 255;
                        hsv.v = 250;
                        break;
                    default:
                        return 0;
                }
        }
    } else {
        hsv.h = randomByte();
        hsv.s = 128;
        hsv.v = 250;
    }
    
    CRGB rgb;
    hsv2rgb_rainbow(hsv, rgb);
    return (rgb.r << 16 ) | (rgb.g << 8) | rgb.b;
}
int randomColor(int offset) {
    return  randomColor2(offset, true);
}
int randomSteadyColor(int offset) {
    return  randomColor2(offset, false);
}

uint8_t randomByte() {
    return (random() >> 16) % 0xff;
}
uint32_t getEndGameDuration() {
    if (emceeMode)
        return endGameDurationEmcee;
    return endGameDurationNormal;
}
void setDigitColor() {
    if (currentAmbientMode != AmbientDefault)
        timeDisplay.setColor(randomSteadyColor(SIDE_STRIP_LENGTH));
    else if (pachinkoState == e_GameOver)
        timeDisplay.setColor(0xffffff);
   else if (pachinkoState == e_Attract)
        timeDisplay.setColor(0x00ff00);
    else {
        
        int secondsRemaining = (gameEnds - now) / 1000;
        if (secondsRemaining < 0)
            secondsRemaining = 0;
        if (secondsRemaining < 10)
            timeDisplay.setColor(0xff4040);
        else if (secondsRemaining < 30)
            timeDisplay.setColor(0xffff00);
        else
            timeDisplay.setColor(0x00ff00);
    }
    
    if (emceeMode) {
        scoreDisplay.setColor(0xffffff);
        scoreDisplay.setValue(score);
        Serial.println("In emcee mode");
    } else {
        switch (currentAmbientMode) {
            case AmbientColor:
            case AmbientPattern:
                scoreDisplay.setColor(randomSteadyColor(SIDE_STRIP_LENGTH));
                break;
            case AmbientDefault:
                scoreDisplay.setColor(0x00ff00);
                break;
        }
        
        scoreDisplay.setValue(score);
    }
}
void newGame() {
    Serial.println("New game");
    lowestPocketsDisabled = false;
    score = 0;
    lowPocketScore = 0;
    currentAmbientMode = AmbientDefault;
    setDigitColor();
    scoreDisplay.setValue(score);
    timeDisplay.setValue(gameDuration);
    LH.gameOver();
    LM.gameOver();
    LL.gameOver();
    RH.gameOver();
    RM.gameOver();
    RL.gameOver();

}

void startGame() {
    Serial.println("Game starting");
    pachinkoState = e_GameInProgress;
    gameStarted = now;
    gameEnds = now + gameDuration * 1000;
    GameOverBell.ring();
    setDigitColor();
    score = 0;
    
}

void switchToIdleMode() {
    newGame();
    if (emceeMode) {
        startGame();
    } else {
        Serial.println("Switching to idle mode");
        pachinkoState = e_Attract;
        GameOverBell.ring(1);
        scoreBell.ring(1);
    }
   }

void switchLowestPockets() {
    if (lowestPocketsDisabled) {
        score += lowPocketScore;
        lowestPocketsDisabled = false;
        scoreBell.ring(1);
    } else {
        Serial.println("Disabling lowest pockets");
        score -= lowPocketScore;
        lowestPocketsDisabled = true;
        GameOverBell.ring(1);
    }
    scoreDisplay.setValue(score);
    
}
void endGame() {
    Serial.println("Game Over");
    GameOverBell.ring(endGameBellRings);
    pachinkoState = e_GameOver;
    timeDisplay.setColor(0xffffff);
    timeDisplay.setValue(0);
    scoreDisplay.setValue(score);
    numGames++;
    sumAllScores += score;
    gameEnds = now;
    lowestPocketsDisabled = false;
    
    EEPROM.put(12,numGames);
    EEPROM.put(14,sumAllScores);
    if (score > maxAllScores) {
        maxAllScores = score;
        EEPROM.put(16,maxAllScores);
    }
    
    
}

void checkPockets() {
    LH.isOverheated();
    LH.checkAndUpdate();
     LM.isOverheated();
    LM.checkAndUpdate();
    if (lowestPocketsDisabled)
        LL.disable();
    else {
        LL.checkAndUpdate();
        if (LL.isOverheated()) 
            switchLowestPockets();
    }
    RH.checkAndUpdate();
    RH.isOverheated();
    RM.checkAndUpdate();
    RM.isOverheated();
    if (lowestPocketsDisabled)
        RL.disable();
    else {
        RL.checkAndUpdate();
        if (RL.isOverheated())
            switchLowestPockets();
    }
}


void scorePoints(int points) {
    if (pachinkoState == e_GameOver)
        return;
    
    if (pachinkoState == e_Attract)
        startGame();
    int multiplier = 1;
    int secondsRemaining = (gameEnds - millis()) / 1000;
    if (secondsRemaining < 10)
        multiplier = 3;
    else if (secondsRemaining < 30)
        multiplier = 2;
    score += points * multiplier;
    if (points == 3)
        lowPocketScore += points * multiplier;
    scoreDisplay.setValue(score);
    scoreBell.ring(points * multiplier);

}

void setupMain() {
    Serial.begin(9600);
    Serial.println("Hello");
    leds.begin();
    leds.show();
    io.begin();
    setupRemote();
    for(int i = 0; i < numRemotes; i++)
        EEPROM.get(start_RemoteEnabled+i, remoteEnabled[i]);

    io.pinMode(AmbientPin, OUTPUT);
    io.digitalWrite(AmbientPin, 1);
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
    
    EEPROM.get(12,numGames);
    EEPROM.get(14,sumAllScores);
    EEPROM.get(16,maxAllScores);
    Serial.print("num games: ");
    Serial.println(numGames);
    Serial.print("sum all scores: ");
    Serial.println(sumAllScores);
    Serial.print("max all scores: ");
    Serial.println(maxAllScores);
    switchToIdleMode();
    
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

void resumeGame() {
    gamePaused = false;
    io.digitalWrite(AmbientPin, 1);
    leftStrip.fill();
    rightStrip.fill();
    
}

int stripCount = 0;
void loopMain() {
    updateCount++;
    random16_add_entropy( random() );
    now = millis();
    
    uint8_t remoteCommand, remoteNumber;
    readRemote(remoteCommand, remoteNumber);
    RemoteCommand cmd = (RemoteCommand) (remoteCommand & 0x0f);

    if (remoteCommand == 0x2a)
        cmd = command_ShowRemotes;
    else if (remoteCommand == 0x23)
        cmd = command_ToggleRemote;
    uint8_t subCommand = ((remoteCommand >>4) & 0x0f);
    
    if (gamePaused && cmd != command_LongAlarm && cmd != command_PauseGame)
        cmd = command_NOP;
    
    if (!remoteEnabled[remoteNumber]) {
        cmd = command_NOP;
    }
    switch (cmd) {
        case command_NOP:
            break;
        case command_ColorAmbient:
            Serial.println("command_ColorAmbient");
            currentAmbientMode = AmbientColor;
            currentAmbientColorChoice = (AmbientColorChoice) (subCommand-1);
            Serial.printf("Color mode = %d, %d, %d\n", currentAmbientMode, currentAmbientColorChoice, currentAmbientPatternChoice);
    
            setDigitColor();
            leftStrip.fill();
            rightStrip.fill();
            scoreBell.ring(1);
            break;
        case command_PatternAmbient:
            Serial.println("command_PatternAmbient");
            currentAmbientMode = AmbientPattern;
            currentAmbientPatternChoice = (AmbientPatternChoice) (subCommand-1);
            Serial.printf("Color mode = %d, %d, %d\n", currentAmbientMode, currentAmbientColorChoice, currentAmbientPatternChoice);
    
            setDigitColor();
            leftStrip.fill();
            rightStrip.fill();
            scoreBell.ring(1);
            break;
        case command_DefaultAmbient:
            Serial.println("command_DefaultAmbient");
            currentAmbientMode = AmbientDefault;
            setDigitColor();
            leftStrip.fill();
            rightStrip.fill();
            scoreBell.ring(1);
            break;
        case command_WarningLights: Serial.println("command_WarningLights"); warningStarted = now;
            showingWarning = true;
            GameOverBell.ring(1);
            break;
        case command_DisableLowest: Serial.println("command_DisableLowest"); 
            switchLowestPockets();
            break;
        case command_LongAlarm:
            GameOverBell.ringFor(3000);
            Serial.println("command_LongAlarm"); break;
        case command_AdvanceGameState:
            Serial.println("command_AdvanceGameState");
            switch (pachinkoState) {
                case e_Boot:
                    break;
                case e_Attract :
                    startGame();
                    break;
                case e_GameInProgress:
                    endGame();
                    break;
                case e_GameOver:
                    switchToIdleMode();
                    break;
            }
            Serial.printf("Game state now %d\n", pachinkoState);
            break;
        case command_EmceeMode:
            Serial.println("command_EmceeMode");
            emceeMode = true;
            scoreBell.ring(1);
            setDigitColor();
            if (pachinkoState == e_Attract)
                startGame();
            break;
        case command_PauseGame:
            Serial.println("command_PauseGame");
            if (gamePaused) {
                Serial.println("resuming game");

                resumeGame();
                scoreBell.ring(1);
                switch (pachinkoState) {
                    case e_Boot:
                        break;
                    case e_Attract :
                       switchToIdleMode();
                        break;
                    case e_GameInProgress:
                        gameEnds = now + timeRemainingIfResumed;
                        scoreDisplay.setValue(score);
                        break;
                    case e_GameOver:
                         endGame();
                        break;
                }
            } else {
                Serial.println("pausing game");
                

                gamePaused = true;
                timePauseStarted = now;
                emceeMode = false;
                setDigitColor();
                if (pachinkoState == e_GameInProgress)
                     timeRemainingIfResumed = gameEnds - now;
                leftStrip.setColor(0);
                rightStrip.setColor(0);
                LH.disable();
                LM.disable();
                LL.disable();
                RH.disable();
                RM.disable();
                RL.disable();
                timeDisplay.clear();
                scoreDisplay.clear();
                io.digitalWrite(AmbientPin, 0);
                

            }
            break;
        case command_ShowRemotes:
            Serial.println("command_ShowRemotes");
            showEnabledState();
           
            delay(1000);
            leftStrip.fill();
            rightStrip.fill();

            break;
        case command_ToggleRemote:
            Serial.println("command_ToggleRemote");
            
            int r = 3;
            if (remoteEnabled[r])
                remoteEnabled[r] = false;
            else
                remoteEnabled[r] = true;
            EEPROM.put(start_RemoteEnabled+r, remoteEnabled[r]);
            showEnabledState();
            delay(1000);
            leftStrip.fill();
            rightStrip.fill();
            break;
            
    }

    if (gamePaused) {
        int32_t timeSincePause = now - timePauseStarted;
        if (timeSincePause > pauseDuration) {
            Serial.println("Pause timed out");
            resumeGame();
            switchToIdleMode();
        } else {
            timeDisplay.clear();
            timeDisplay.setPixelOfFirstDigit(timeSincePause/500, 0xff0000);
        }
        
    }
    
    if (!gamePaused) {
        checkPockets();
        if (showingWarning) {
            int32_t sinceWarning = now-warningStarted;
            if (sinceWarning > warningDuration) {
                Serial.println("Ending warning");
                showingWarning = false;
                leftStrip.fill();
                rightStrip.fill();
            } else if (sinceWarning % 250 < 125) {
                leftStrip.setColor(0xff0000);
                rightStrip.setColor(0xff0000);
            } else {
                leftStrip.setColor(0);
                rightStrip.setColor(0);
            }
        } else if (stripCount++ == 5 || currentAmbientMode == AmbientPattern) {
            stripCount = 0;
            leftStrip.update();
            rightStrip.update();
        }
        int secondsRemaining = (gameEnds - now) / 1000;
        if (secondsRemaining < 0)
            secondsRemaining = 0;
        
        setDigitColor();
        switch (pachinkoState) {
            case e_Boot:
            case e_Attract:
                timeDisplay.setValue(gameDuration);
                
                break;
                
            case  e_GameInProgress:

                timeDisplay.setValue(secondsRemaining);
                
                if (now > gameEnds)
                    endGame();
                
                break;
                
            case e_GameOver:
                timeDisplay.setValue(0);
                uint32_t sinceGameEnded = now-gameEnds;
                if (sinceGameEnded > getEndGameDuration()) {
                    Serial.println("Game over expired, switching to Idle mode");
                    emceeMode = false;
                    switchToIdleMode();
                } else {
                    long phase = sinceGameEnded % 1000;
                    setDigitColor();
                    if (phase < 500)
                        timeDisplay.setColor(0);
                    timeDisplay.setValue(0);
                }
                break;
        }
    }
    GameOverBell.update();
    scoreBell.update();
    leds.show();
    delay(20);
}

