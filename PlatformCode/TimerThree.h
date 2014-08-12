//
//  TimerThree.h
//  PlatformCode
//
//  Created by Bill on 8/11/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef _TimerThree_
#define _TimerThree_



class TimerThree {
public:
    void initialize(unsigned long);
    void setPeriod(unsigned long);
    void start();
    void stop();
    void attachInterrupt(void (*isr)());
    void detachInterrupt();
    
};

TimerThree Timer3;

#endif
