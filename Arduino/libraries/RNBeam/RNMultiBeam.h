#ifndef RNMultiBeam_h
#define RNMultiBeam_h

#include "AnimationBase.h"

// the animation paints the whole stripe in consecutive HSV color

class RNMultiBeam : public AnimationBase
{
	public:
	 RNMultiBeam(LedLampe& l) : AnimationBase(l)
	 {}
	 void setup();
	 void paint( uint32_t frame );
	 void cleanup();
	private:
};

#endif
