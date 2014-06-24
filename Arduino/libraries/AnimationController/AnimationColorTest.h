#ifndef ANIMATION_COLOR_TEST_H
#define ANIMATION_COLOR_TEST_H

#include "AnimationBase.h"

// the animation paints the whole stripe in consecutive HSV color

class AnimationColorTest : public AnimationBase
{
	public:
	 AnimationColorTest() : AnimationBase()
	 {}
	 void setup();
	 void paint( uint32_t frame );
	 void cleanup();
	private:
};

#endif
