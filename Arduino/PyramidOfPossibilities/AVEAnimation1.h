//
//  AVEAnimation1.h
//  PlatformData
//
//

#ifndef __AVEAnimation1__
#define __AVEAnimation1__

#include "RNAnimation.h"
#include "RNLights.h"

class AVEAnimation1 : public RNAnimation {
public:

    AVEAnimation1(RNInfo & info, unsigned long animationStartMillis);;
    virtual void paint(RNLights & lights);
    virtual const char * name();

private:
    bool forward;
    unsigned long lastUpdate;
    uint16_t currentPos;
};

#endif /* defined(__AVEAnimation1__) */
