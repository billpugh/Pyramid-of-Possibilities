#ifndef AnimationBase_h
#define AnimationBase_h

#include "LedLampe.h"
//#include "AnimationController.h"

// Base class to be subclassed by all animations so the AnimationController can display it
class AnimationBase 
{
  public:
  /* the way it should work without circular include problems:
    AnimationBase(AnimationController& c)
		: _animationController(c),
		  _ledLampe(c.getLedLampe())
	{
	}
	*/
    AnimationBase(LedLampe& l)
		: _ledLampe(l)
	{
	}
	
	// create stuff the animation needs here:
	virtual void setup();
	
	// will be called by the animation controller when enough time elapsed to display the next frame
	// @parameter frame: the frame number to be displayed. 
	virtual void paint( uint32_t frame );
	
	// do clean up here
	virtual void cleanup();
	
  protected:
	LedLampe& _ledLampe;
//	AnimationController& _animationController;
};
#endif
