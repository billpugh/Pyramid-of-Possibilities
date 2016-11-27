#ifndef RAINBOWWHEELDEMO_H
#define RAINBOWWHEELDEMO_H

#include "Demo.h"

// Animation speeds to loop through with mode presses.  The current milliseconds 
// are divided by this value so the smaller the value the faster the animation.

extern Adafruit_NeoPixel foo;

class RainbowWheelDemo: public Demo {
public:
  RainbowWheelDemo() {   }
  ~RainbowWheelDemo() {}

  virtual void loop() {
    updateRotation();
    int offset = (int) (currentAngle/twoPi*wheelPixels);
   Serial.print(avgAngle);
   Serial.print("  ");
   Serial.println(offset);
    // Loop through each pixel and set it to an incremental color wheel value.
    for(int i=0; i<wheelPixels; ++i) {
      foo.setPixelColor(i, CircuitPlayground.colorWheel((((i+offset) * 256 / wheelPixels) ) & 255));
    }
    // Show all the pixels.
    foo.show();
  }

  virtual void modePress() {
    
  }


};


#endif
