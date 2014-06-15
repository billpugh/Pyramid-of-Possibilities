#ifndef __RNBEAM__
#define __RNBEAM__

#include <stdint.h>

class RNBeam {

public:
  RNBeam();
  ~RNBeam();

  // Light Properties
  uint32_t range; // maxval - minval
  uint32_t halfrange; // range/2
  uint32_t maxval; // max position
  uint32_t minval;  // min position
  uint32_t speed;
  double width; // width (in same units as pos, maxval, minval) of a strobe band
  double width_speed;
  int8_t width_direction;
  int8_t direction_sign;  // -1 or 1, set programatically.
  uint16_t offset;  // determine the starting position (ie. when millis() is 0)

  // Color properties & methods
  uint32_t color_for_distance (double d);
  uint32_t combine_colors(uint32_t a, uint32_t b);
  uint8_t r, g, b;   // RGB of the light beam. We use a percentage multiples by each of these values.

  // Light Strip
  void *strip;  // Adafruit_NeoPixel    // NOT USED (YET). Should be using RNLights instead of Adafruit_NeoPixel
  uint16_t numLights;

  // Public Methods
  void loop();
  void draw();
  uint32_t drawPixel(uint16_t i);
  double position_of_led_center (uint32_t led_id);
  int calc_distance(int x, int y);

  uint32_t min_range_of_lights_to_draw; // set when loop() is called. may be > maxval so use modulus
  uint32_t max_range_of_lights_to_draw; 
private:
  uint32_t convertCoordinateToLED(int coordinate, int8_t roundingDirection);
  uint16_t position;
};

#endif /* defined(__RNBEAM__) */