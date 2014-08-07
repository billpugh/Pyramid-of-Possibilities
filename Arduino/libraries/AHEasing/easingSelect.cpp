
#include "easingSelect.h"

AHEasingFunction getEasingFunction(EasingMode mode, CurveType curve) {

	switch(curve)
	{
		default:
		case CurveTypeLinear:
			return LinearInterpolation;
			break;
		case CurveTypeQuadratic:
			return (mode == EaseIn) ? QuadraticEaseIn : (mode == EaseOut) ? QuadraticEaseOut : QuadraticEaseInOut;
			break;
		case CurveTypeCubic:
			return (mode == EaseIn) ? CubicEaseIn : (mode == EaseOut) ? CubicEaseOut : CubicEaseInOut;
			break;
		case CurveTypeQuartic:
			return (mode == EaseIn) ? QuarticEaseIn : (mode == EaseOut) ? QuarticEaseOut : QuarticEaseInOut;
			break;
		case CurveTypeQuintic:
			return (mode == EaseIn) ? QuinticEaseIn : (mode == EaseOut) ? QuinticEaseOut : QuinticEaseInOut;
			break;
		case CurveTypeSine:
			return (mode == EaseIn) ? SineEaseIn : (mode == EaseOut) ? SineEaseOut : SineEaseInOut;
			break;
		case CurveTypeCircular:
			return (mode == EaseIn) ? CircularEaseIn : (mode == EaseOut) ? CircularEaseOut : CircularEaseInOut;
			break;
		case CurveTypeExpo:
			return (mode == EaseIn) ? ExponentialEaseIn : (mode == EaseOut) ? ExponentialEaseOut : ExponentialEaseInOut;
			break;
		case CurveTypeElastic:
			return (mode == EaseIn) ? ElasticEaseIn : (mode == EaseOut) ? ElasticEaseOut : ElasticEaseInOut;
			break;
		case CurveTypeBack:
			return (mode == EaseIn) ? BackEaseIn : (mode == EaseOut) ? BackEaseOut : BackEaseInOut;
			break;
		case CurveTypeBounce:
			return (mode == EaseIn) ? BounceEaseIn : (mode == EaseOut) ? BounceEaseOut : BounceEaseInOut;
			break;
	}
}

