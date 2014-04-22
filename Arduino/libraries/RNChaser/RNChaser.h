//
//  RNChaser.h
//
//  Created by Bill on 3/24/14.
//  Copyright (c) 2014 Radical Norm. All rights reserved.
//

#ifndef __RNChaser__
#define __RNChaser__

#include <stdint.h>

#include "RNLights.h"

class RNChaser {
    
public:
    RNChaser(RNLights & lights);
    bool update(unsigned long millis); 
    void setRPM(uint16_t rpm); 
    uint16_t getRPM();
    void fade(uint8_t amount=1);
    
    bool forward;
    bool active;
    unsigned long nextUpdate;
    uint16_t delay;
    int16_t position;
    uint8_t r,g,b;
    private:
    RNLights & lights;
};

#endif /* defined(__RNChaser__) */
