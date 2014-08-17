OK, we now have one uniform way to handle tweaking a animation. 

There is one 8-bit value that is adjusted up or down using the up/down arrow keys. 

Central also interprets it as a signed cycles per minute value, and using that to compute cycles-at-last-tweak value. If you simply computed cycles as cyclesPerMinute * animationTimeInMinutes(), things wouldn't move smoothly when you adjusted the cyclesPerMinute up/down. So everytime the value is tweaked, it updates a cycles-at-last-tweak value, so the current cycle count is computed by the teensies as:
    
   cycles = cycles-at-last-tweak + currentCyclesPerMinute * timeInMinutesSinceLastTweak()

There is a (server side) animation parameter which says whether the tweak value is:
	
* capped at -127 to 127 (e.g., a cycles/minute value)
* capped at 0 to 255 (e.g., a brightness value)
* wrapping: tweaking up from 255 gives 0 (e.g., a hue)

All parameters other than tweakable parameters are constant for the duration of the animation.

An animation can also look at the last time the value was tweaked, and trigger something if the value was tweaked since the last time the paint method was called.

So, in essence, a tweakable animation should choose one of the following ways to allow central to tweak the animation:

* `getAnimationCycles()` - Let central control the speed, or even reverse an animation, and maintain the cycle count for you. Generally, the fractional amount tells you what portion of a cycle has been completed, and the integer part tells you have many complete cycles have gone by.
* `getTweakValue()` - returns a 8 bit tweakable value
* `hasBeenTweaked()` - returns true if it has been tweaked since the last call to `hasBeenTweaked()`

