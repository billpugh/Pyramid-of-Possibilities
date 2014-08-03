/* 
 * File:   AVEFlashesAnimation.h
 * Author: antoine
 *
 * Created on August 2, 2014, 4:50 PM
 */

#ifndef AVEFLASHESANIMATION_H
#define	AVEFLASHESANIMATION_H

#include "RNAnimation.h"
#include "RNLights.h"

class AVEFlashesAnimation : public RNAnimation {
public:

    AVEFlashesAnimation(RNInfo & info, unsigned long animationStartMillis);
    virtual void paint(RNLights & lights);
    virtual const char * name();

private:
};

#endif	/* AVEFLASHESANIMATION_H */

