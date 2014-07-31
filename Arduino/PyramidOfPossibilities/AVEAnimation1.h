//
//  AVEAnimation1.h
//  PlatformData
//
//

#ifndef __PlatformData__AVEAnimation1__
#define __PlatformData__AVEAnimation1__

#include "RNAnimation.h"
#include "RNLights.h"
#include "RNChaser.h"

class AVEAnimation1 : public RNAnimation {
public:

    AVEAnimation1(RNInfo & info, unsigned long animationStartMillis);;
    virtual void paint(RNLights & lights);
    virtual char * name();

private:
    bool forward;
    unsigned long lastUpdate;
    uint16_t currentPos;
};

#endif /* defined(__PlatformData__AVEAnimation1__) */
