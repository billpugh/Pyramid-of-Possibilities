/**
Proposal for a C++ Interface to non-blocking Animations.

this package consists of following files:
- BM_InterfaceSample.ino	:	This file ;-) creates all necessary objects and contains the setup() and loop() routines
- LedLampe.cpp/.h			:	A class derived from Adafruit_NeoPixel. This basically is the LED-stripe with some additional
								methods which fit to Milo's hardware. If we want to use this concept we would probably have to 
								replace this with a PoP specific class.
- AnimationBase.cpp/.h		:	An interface class for all animations. If we want to create a new Animation we need to subclass 
								this class and overwrite the setup() paint() and cleanup() functions. An example of such an subclass
								is given in AnimationRainbow.
-AnimationRainbow.cpp/.h	:	A very simple animation class that paints the whole stripe with HSV values. This basically is the 
								Rainbow function of the Adafruit_NeoPixel library without delay.
-AnimationController.cpp/.h	:	A controller class that manages when to paint a new frame of an animation. It currently can handle 
								only a single Animation (a subclass of AnimationBase). An example how to use it can be found in 
								BM_InterfaceSample.ino
								Contains the #define ANIMATIONCONTROLLER_MILLISPERFRAME which says how much millis must have passed 
								until the next frame is shown

*/
/*
#include <Adafruit_NeoPixel.h>
#include "LedLampe.h"
#include "AnimationBase.h"
// #include "AnimationRainbow.h"
#include "AnimationController.h"

// create a led stripe:
LedLampe matrix = LedLampe(121, 6, NEO_GRB + NEO_KHZ800);

// create the animation controller and initialize it with the stripe:
AnimationController animationController = AnimationController(matrix);

// create an animation. actually this class only needs to know about the animation controller,
// but i get a problem with circular includes so we tell the animation what the stripe is for now:
AnimationRainbow aniRainbow = AnimationRainbow(matrix);

void setup()
{
  pinMode(13, OUTPUT);
  matrix.begin();
 
 // need to be done once:
  animationController.RegisterAnimation(&aniRainbow);
  
  Serial.begin(115200); 
}

void loop()
{
  unsigned long currentMillis = millis(); // holds the timepoint of the last Serial comm 

  // need to be done in the main loop:
  animationController.setCurrentMillis(currentMillis);  	// tells the controller what time it is
  animationController.PlayAnimation();						// will only do something if ANIMATIONCONTROLLER_MILLISPERFRAME millis passed since last frame
}
*/

