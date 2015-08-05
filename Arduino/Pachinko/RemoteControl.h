//
//  RemoteControl.h
//  PachinkoTestbed
//
//  Created by Bill on 8/5/15.
//
//

#ifndef __PachinkoTestbed__RemoteControl__
#define __PachinkoTestbed__RemoteControl__

#include <stdio.h>
#include <stdint.h>

enum  RemoteCommand {
    command_NOP,
    command_ColorAmbient,
    command_PatternAmbient,
    command_DefaultAmbient,
    
    command_WarningLights,
    command_DisableLowest,
    command_LongAlarm,
    
    command_AdvanceGameState,
    command_EmceeMode,
    command_PauseGame};


extern void setupRemote();
extern uint8_t readRemote(void);
#endif /* defined(__PachinkoTestbed__RemoteControl__) */
