The Animation class is what is implemented by code that draws an animation.

	class Animation {
		// Constructor that initializes the info field
		Animation(Info & info);
		// Local reference to the info object
		Info & info;
		// Called before calling setup, to give the global time when this animated started

		 // Gives the time in milliseconds since this animation starter
		final unsigned long getAnimationMillis();
		
		// Called if there are any parameters from central
		void setParameters(int size, char * data);
		// Request that the animation set the lights appropriately. 
		// For a base animation, the lights will be entirely black before the call
		void paint(RNLights & lights);


		
		}

Sprites are animations that typically have a short lifespan and are drawn on top of the color buffer resulting from the base animation (and perhaps other sprites). Sprites are dynamically created, and there may be an unknown 
	  
	class Sprite : Animation {
		
		uint16_t x,y,z;
	  



The Info class is how an Animation learns about its environment.

	  
	 class Info {
	   unsigned long getGlobalMillis();
	   float getGlobalActivity();
	   float getLocalActitiviity();
	   uint8_t getTaps();
	   float getAccelerometerData(float data[3]);
	   
	   // Information about the platform
	   const uint8_t tier;
	   const uint8_t number;
	   const uint8_t identifier;
	   const int16_t x,y,z;
	   
	   // getGlobalAngle for LED in degrees (0 = south)
	   uint16_t getGlobalAngle(uint8_t led);
	   
	   }
  