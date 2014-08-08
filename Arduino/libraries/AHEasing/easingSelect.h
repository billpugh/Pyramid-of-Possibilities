
#ifndef AH_EASING_H_SELECT
#define AH_EASING_H_SELECT

#include "easing.h"

enum CurveType
{
        CurveTypeLinear,
        CurveTypeQuadratic,
        CurveTypeCubic,
        CurveTypeQuartic,
        CurveTypeQuintic,
        CurveTypeSine,
        CurveTypeCircular,
        CurveTypeExpo,
        CurveTypeElastic,
        CurveTypeBack,
        CurveTypeBounce,
};

enum EasingMode
{
        EaseIn,
        EaseOut,
        EaseInOut,
};

AHEasingFunction getEasingFunction(EasingMode mode, CurveType curve);

#endif
