//
//  UploadParameters.cpp
//  PlatformCode
//
//  Created by Bill on 8/16/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Constants.h"
#include "UploadParameters.h"
#include "RNInfo.h"
#include "Arduino.h"
#include "RNAnimation.h"


void printParameters(RNInfo &info,  AnimationEnum a) {
    RNAnimation * animation = getAnimation(info, a);
    int size = animation->parametersSize;
    info.println("OK");
    info.printf("%d\n", a);
    info.println(animation->name());
    info.printf("%d\n", size);
    uint8_t * p = (uint8_t *)animation->parametersPointer;

    for(int i = 0; i < size; i++)
        info.printf("%02x", (uint8_t)p[i]);
    info.println("");

    delete animation;

}
void setupUploadParameters() {
    Platform platform( /* ID */ 42, /* XYZ */ 0,0,700,
                      /* dir */ 0, /* wire Pos */ 1);
    RNInfo info(constants.LEDs, platform);
    int a = 1;// Serial.read();
    if (a< 0 && a >= e_AnimationCount) {
        info.printf("Got bad byte %d\n",a);

        return;
    }

    for(int i = 0; i < e_AnimationCount; i++) {
        printParameters(info, (AnimationEnum) i);
    }



}
