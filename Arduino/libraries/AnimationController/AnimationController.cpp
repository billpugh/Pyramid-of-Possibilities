#include "AnimationController.h"

void AnimationController::RegisterAnimation(AnimationBase* animation)
{
  if( _currentAnimation != NULL )
	_currentAnimation->cleanup();
	
  _currentAnimation = animation;
  _currentAnimation->setup();
}

void AnimationController::SetupAnimation()
{
  if( _currentAnimation != NULL )
    _currentAnimation->setup();
}

void AnimationController::PlayAnimation()
{
  if( _currentAnimation != NULL )
  {
    if( _millisCurrent - _millisOfLastFrame > ANIMATIONCONTROLLER_MILLISPERFRAME )
	{
      _currentAnimation->paint(_frameCurrent);
	  _frameCurrent++;
	  _millisOfLastFrame = _millisCurrent;
	}
  }
}

void AnimationController::CleanupAnimation()
{
  if( _currentAnimation != NULL )
    _currentAnimation->cleanup();
}

LedLampe& AnimationController::getLedLampe()
{
  return _ledLampe;
}

void AnimationController::setCurrentMillis(unsigned long millis)
{
  _millisCurrent = millis;
}