// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include "led_sysdefs.h"
#include "hsv2rgb.h"
#include "Adafruit_NeoPixel.h"
//#include "OctoWS2811.h"
#include "RNLightsNeoPixel.h"

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      12

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels0 = Adafruit_NeoPixel(29, 2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels1 = Adafruit_NeoPixel(12, 10, NEO_GRB + NEO_KHZ800);

RNLightsNeoPixel lights0(pixels0);
RNLightsNeoPixel lights1(pixels1);

int delayval = 500; // delay for half a second

void setup() {

lights0.show();
lights1.show();

}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for (int i = 0; i < 29; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    lights0.setPixelColor(i, pixels0.Color(0, 150, 0)); // Moderately bright green color.
    lights0.show(); // This sends the updated pixel color to the hardware.
     delay(delayval); // Delay for a period of time (in milliseconds).
  }
  for (int i = 0; i < 12; i++) {

    lights1.setPixelColor(i, pixels1.Color(150, 0, 0)); // Moderately bright green color.
    lights1.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
}
