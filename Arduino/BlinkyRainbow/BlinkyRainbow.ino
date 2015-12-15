#include <FastLED.h>

#define LED_COUNT 50 // BlinkyTape has 60 LEDs!
struct CRGB leds[LED_COUNT]; // this struct contains 60 CRGB values.  This is where 

#define PIN_BUTTON 10
#define PIN_IO_A   7
#define PIN_IO_B   11
#define PIN_SIGNAL 13
#define PIN_INPUT  10

int color_set = 0;

// first, let's get ready to blink using some FastLED routines
// take a look at the FastLED example called Fast2Dev for more usage info
void setup()
{  
  LEDS.addLeds<WS2812B, PIN_SIGNAL, RGB>(leds, LED_COUNT); // this configures the BlinkyBoard - leave as is.
  LEDS.showColor(CRGB(0, 0, 0)); // set the color for the strip all at once.
  LEDS.setBrightness(50); // start out with LEDs off
  LEDS.show(); // you'll always need to call this function to make your changes happen.
}

int count = 0;
// this is the main loop where we call the other functions. 
void loop() {
   for (uint8_t i = 0; i < LED_COUNT; i++) {
    int hue = (int)(128*(1+sin(3.0*(i+count/5.0)/LED_COUNT)));
    if (hue < 0)
      hue = 0;
    else if (hue > 255)
      hue = 255;
    int value = (int)(200*(abs(sin(-10.0*(i+count/5.0)/LED_COUNT))));
    if (value < 0)
      value = 0;
    else if (value > 255)
      value = 255;
    leds[i] = CHSV(hue, 255, value);
   }
   LEDS.show();
   count++;
   delay(20);
}
