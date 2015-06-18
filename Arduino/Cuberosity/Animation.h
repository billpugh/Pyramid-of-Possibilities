//
//  Animation.h
//  Cuberosity
//
//  Created by Bill on 6/10/15.
//
//

#ifndef __Cuberosity__Animation__
#define __Cuberosity__Animation__

#include <stdio.h>

class Animation {

    public:
    Animation() {};
    virtual ~Animation() {};
    virtual void prepare() {};
    virtual void setPixel(int pos, int side, int height, int horizontalOffset) {};

};

#endif /* defined(__Cuberosity__Animation__) */
