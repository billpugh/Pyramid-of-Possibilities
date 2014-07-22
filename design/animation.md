The RNAnimation class is what is implemented by code that draws an animation. 

	class RNAnimation {
	public:
	    // Constructor
	    RNAnimation(RNInfo & info, unsigned long animationStartMillis);
	    // Local reference to the info object
	    RNInfo & info;
	    
	    // Gives the time in milliseconds since this animation started
	    unsigned long getAnimationMillis();
	    
	    // Called if there are any parameters from central
	    virtual void setParameters(int size, char * data);
	    
	    // Request that the animation set the lights appropriately.
	    // For a base animation, the lights will be entirely black before the call
	    virtual void paint(RNLights & lights);
	    }
    
For example, I defined a animation named WWPAnimation1, that simply sets all lights to the same color, rotating the hue through the rainbox every 2.56 seconds.

	class WWPAnimation1 : public RNAnimation {
	public:
	    WWPAnimation1(RNInfo & info, unsigned long animationStartMillis)
	    : RNAnimation(info, animationStartMillis) {};
	    virtual void paint(RNLights & lights);
	};

The implementation of the paint method is:

	void WWPAnimation1::paint(RNLights & lights) {
	    uint8_t hue = (getAnimationMillis() / 10) % 256;
	    lights.setAllPixelHSVs(hue, 255, 255);
	   }

Note that when an animation is started, it is allocated using new, so all initialization should go into the constructor. When an animation is finished, it is deallocated using delete, so any cleanup code should go in the destructor.


Right now, the controller code is trivial. It just takes a list of animations, and rotates though them, 10 seconds each. More sophisication where will come later. At the moment, we aren't handling any parameters, so the setParameters method won't be called on an animation.

Once you have written an animation class, this is how you get it shown. Assume, for example, I've written a class WWPAnimation4. These are the steps:

Edit Animations.h, and edit the enumeration AnimationEnum to include an enum value for the class you've added. For example, I would add e_WWPAnimation4 after e_WWPAnimation3 in the following code:

	enum  AnimationEnum {
	
	  // Animations defined by Bill Pugh (WWP)
	  e_WWPAnimation1,
	  e_WWPAnimation2,
	  e_WWPAnimation3,
	
	  // Not an actual enum, just the value used to give us the count of the number of enums
	  e_AnimationCount}; 

Edit Animations.cpp. Add a #include for your header file, and add a case to the switch statement in the method getAnimation:

	RNAnimation * getAnimation(AnimationEnum a, RNInfo & info, long unsigned animationStartMillis ) {
	  switch (a) {
	
	    // Animations by WWP
	  case e_WWPAnimation1 : 
	    return new WWPAnimation1(info, animationStartMillis);
	  case e_WWPAnimation2 : 
	    return new WWPAnimation2(info, animationStartMillis);
	  case e_WWPAnimation3 : 
	    return new WWPAnimation3(info, animationStartMillis);
	
	  default:
	    return 0;
	  }
	}

And that is it, you are done. 

Now, for many animations, you will want to know more than the time since the animation started. An animation gets that information from the RNInfo object that is stored as part of the object. The RNInfo object supports the following methods and constants:

	class RNInfo {
	public:
	
	 // Information about the platform
	  // Number of visible LEDs on the platform
	  const uint8_t numLEDs;
	  // What tier is the platform on
	  const uint8_t tier;
	  // What is the number of the platform within that tier
	  const uint8_t number;
	  // What is the identify of the platform (unique)
	  const uint8_t identifier;
	
	  // What is the x,y,z displacement of the center of the platform 
	  // from the center base of the Pyramid
	  const int16_t x,y,z;
	  // Get the global clock value (synchronized across all platforms)
	  unsigned long getGlobalMillis();
	
	  // Get the most recent reading from the accelerometer, combine all three axes. 
	  // Non-negative, passed through a high pass filter, will be 0.0 when everything is absolutely still.
	  float getLocalActitiviity();
	  // Get the individual x,y,z accelerometer readings passed through a high pass filter. Values may be negative. 
	  void getLocalXYZActitiviity(float data[3]);
	  // Get whether or not taps have been detected since the last paint refresh. If zero, no taps have been indicated. 
	  // This is a bit field, with different bits indicating whether the tap was in the X, Y or Z direction, 
	  // and whether it was positive or negative. In most cases, it is sufficient to check whether or not this value is nonzero.
	  // Bits are: 
	  // AxX: 0x10 -- tap in X axis
	  // PxX: 0x01 -- positive in X axis
	  // AxY: 0x20 -- tap in Y axis
	  // PxY: 0x02 -- positive in Y axis
	  // AxZL 0x40 -- tap in Z axis
	  // PxZ: 0x04 -- positive in Z axis
	  uint8_t getTaps();
	
	  // get the number of milliseconds since the last tap
	  unsigned long timeSinceLastTap();
	
	  // Get a combined indication of activity across all platforms. Same scale as getLocalActivity
	  float getGlobalActivity();
	
	  // getGlobalAngle for LED in degrees (0 = south)
	  uint16_t getGlobalAngle(uint8_t led);
	  }
	  
For example, here is an animation paint method that is bright for the second after a tap:

	void WWPAnimation3::paint(RNLights & lights) {
	
	  unsigned long since = info.timeSinceLastTap();
	
	  int brightness = 50;
	  if (since < 1000)
	    brightness = 250 - since/5;
	  uint8_t hue = (getAnimationMillis() / 5) % 256;
	
	  lights.setAllPixelHSVs(hue, 255, brightness);
	}


OK, that is it for now, and I hope that is enough to allow people to start creating some animations. Let me know if you have any questions.

I'll be working on sprites soon, and provide documentation of those after I get them working.
  

Sprites are animations that typically have a short lifespan and are drawn on top of the color buffer resulting from the base animation (and perhaps other sprites).