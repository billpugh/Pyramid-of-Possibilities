//
//  Animations.cpp
//  Cuberosity
//
//  Created by Bill on 6/10/15.
//
//

#include "Animations.h"
#include "TimeRainbowGradient.h"
#include "RGBHeartBeat.h"
#include "RadialGradient.h"
#include "VerticalGradient.h"
#include "TimeGradient.h"
#include "easingSelect.h"


AnimationEnum nextAnimation(AnimationEnum a ) {
    a = (AnimationEnum) (a+1);
    if (a == e_AnimationCount)
        return firstAnimation();
    else return a;
    
}
AnimationEnum firstAnimation( ) {
    return  (AnimationEnum) (0);
    
}


Animation * getAnimation(AnimationEnum a ) {
    switch (a) {
            
        case e_TimeRainbowGradient:
            return new TimeRainbowGradient();
            
        case e_RGBHeartBeat:
            return new RGBHeartBeat();
        case e_RadialGradient:
            return new RadialGradient();
        case   e_VerticalGradient:
            return new VerticalGradient(RNGradient(1, RNGradientWrap, 0x00ff80, 0xffff80));
        case   e_VerticalGradientBlue:
            return new VerticalGradient(RNGradient(1, RNGradientBounce, 0x90ff80, 0xffff80));
        case   e_VerticalGradientRed:
            return new VerticalGradient(RNGradient(1, RNGradientBounce, 0x00ff80, 0x40ff80));
        case e_WhiteGlow:
            return new TimeGradient(
                                    getEasingFunction(EaseInOut, CurveTypeCubic),
                                    getEasingFunction(EaseIn,
                                                      CurveTypeCubic),
                                    
                                    RNGradient(0, RNGradientBounce, 0x202020, 0xffffff),
                                    10
                                    );
        case e_GreenPurpleGlow:
            return new TimeGradient(
                                    getEasingFunction(EaseInOut, CurveTypeCubic),
                                    getEasingFunction(EaseIn,
                                                      CurveTypeCubic),
                                    
                                    RNGradient(1, RNGradientBounce, 0x80ff80, 0xffff80),
                                    10
                                    );
        default :
            return new TimeRainbowGradient();
    }
}
