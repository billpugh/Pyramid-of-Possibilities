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

enum  PachinkoState {
    e_Boot,
    e_Attract,
    e_GameInProgress,
    e_GameOver};

extern RNNumberDisplay scoreDisplay, timeDisplay;

void setupMain();

void loopMain();

#endif /* defined(__PachinkoCode__PachinkoMain__) */
