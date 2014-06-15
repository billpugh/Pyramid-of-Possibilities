#ifndef AnimationController_h
#define AnimationController_h

// how much millis must be passed until the next frame is displayed.
// this is the inverse of a framerate:
#define ANIMATIONCONTROLLER_MILLISPERFRAME 10

#include "LedLampe.h"
#include "AnimationBase.h"

// AnimationController displays a frame when enough time passed since the last frame display
class AnimationController 
{
  public:
    AnimationController(LedLampe& l) 
		: _ledLampe(l),
		  _currentAnimation(NULL),
		  _millisOfLastFrame(0),
		  _millisCurrent(0),
		  _frameCurrent(0)
	{
	}
	void RegisterAnimation(AnimationBase* animation);
	void SetupAnimation();
	void PlayAnimation();
	void CleanupAnimation();
	void setCurrentMillis(unsigned long millis);
	LedLampe& getLedLampe();
	
  private:
    LedLampe& _ledLampe;
	AnimationBase* _currentAnimation;
	unsigned long _millisOfLastFrame; 	// the timepoint when a frame was painted
	unsigned long _millisCurrent;		// the current timepoint
	uint32_t _frameCurrent;
};
#endif
