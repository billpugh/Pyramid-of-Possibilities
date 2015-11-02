#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <stdlib.h>
#include "AnimationBase.h"
#include "AnimationController.h"
#include "AnimationColorTest.h"

// create the animation controller and initialize it with the stripe:
AnimationController animationController = AnimationController();
AnimationColorTest animation1 = AnimationColorTest();

void setup()
{
  pinMode(13, OUTPUT);

  Serial.begin(115200);

   // need to be done once:
  animationController.RegisterAnimation(&animation1);
}

void loop()
{
  unsigned long currentMillis = millis(); // holds the timepoint of the last Serial comm 

  // need to be done in the main loop:
  animationController.setCurrentMillis(currentMillis);  	// tells the controller what time it is
  animationController.PlayAnimation();						// will only do something if ANIMATIONCONTROLLER_MILLISPERFRAME millis passed since last frame
}