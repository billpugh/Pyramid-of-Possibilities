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

extern PachinkoState pachinkoState;

extern RNNumberDisplay scoreDisplay, timeDisplay;

extern Bell GameOverBell, ScoreBell;

void setupMain();

void loopMain();


void scorePoints(int score);

#endif /* defined(__PachinkoCode__PachinkoMain__) */
