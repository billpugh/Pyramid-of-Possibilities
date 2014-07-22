//
//  RNShow.h
//  RNShow
//
//  Created by Bill on 6/15/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef __RNShow__RNShow__
#define __RNShow__RNShow__

#include "RNLights.h"

class RNShow {
    public:
    RNShow(RNLights &lights);
    unsigned long getMillis();
    void setMillis(unsigned long millis);
    virtual ~RNShow();
    virtual void accelerometerCallback( float totalG,
                               float directionalG[3],
                               uint8_t tapSource);
    virtual bool update(unsigned long millis) = 0;
    virtual bool active() = 0;
protected:
    RNLights & lights;
private:
    unsigned long ms;
};



#endif /* defined(__RNShow__RNShow__) */
