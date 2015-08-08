//
//  PachinkoMain.h
//  PachinkoCode
//
//  Created by Bill on 4/23/15.
//
//

#ifndef __PachinkoCode__PachinkoMain__
#define __PachinkoCode__PachinkoMain__

#include <stdio.h>
#include "RNNumberDisplay.h"
#include "Bell.h"

enum  PachinkoState {
    e_Boot,
    e_Attract,
    e_GameInProgress,
    e_GameOver};

enum AmbientMode {
    AmbientDefault,
    AmbientColor,
    AmbientPattern};

enum AmbientColorChoice {
AmbientRed,
AmbientGreen,
AmbientBlue,
AmbientYellow,
AmbientMagenta,
AmbientCyan,
    AmbientWhite};

enum AmbientPatternChoice {
    AmbientRainbow,
    AmbientComets,
    AmbientSparkles};

extern int AmbientColorHue[];


extern AmbientMode currentAmbientMode;
extern AmbientColorChoice currentAmbientColorChoice;
extern AmbientPatternChoice currentAmbientPatternChoice;
extern PachinkoState pachinkoState;

extern RNNumberDisplay scoreDisplay, timeDisplay;

extern Bell GameOverBell, ScoreBell;

void setupMain();

void loopMain();

int scoreMultiplier();

uint8_t randomByte();

int randomColor(int offset);
int randomSteadyColor(int offset);
void scorePoints(int score);

#endif /* defined(__PachinkoCode__PachinkoMain__) */
