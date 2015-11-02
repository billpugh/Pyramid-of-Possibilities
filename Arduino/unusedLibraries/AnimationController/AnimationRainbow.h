// led lampe

#ifndef AnimationRainbow_h
#define AnimationRainbow_h

#include "AnimationBase.h"

// the animation paints the whole stripe in consecutive HSV color

class AnimationRainbow : public AnimationBase
{
	public:
	 AnimationRainbow(LedLampe& l) : AnimationBase(l)
	 {}
	 void setup();
	 void paint( uint32_t frame );
	 void cleanup();
	private:
};

#endif
