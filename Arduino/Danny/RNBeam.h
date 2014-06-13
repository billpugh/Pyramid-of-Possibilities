#ifndef __RNBEAM__
#define __RNBEAM__

#include <stdint.h>

class RNBeam {

public:
  RNBeam();
  ~RNBeam();


  uint32_t maxval; // max position
  uint32_t minval;  // min position
  uint32_t speed;
  uint32_t range;
  double width; // width (in same units as pos, maxval, minval) of a strobe band
  int8_t direction_sign;  // -1 or 1, set programatically.

  void *strip;  // Adafruit_NeoPixel 
  uint16_t numLights;

  void loop();
  void draw();
  uint32_t drawPixel(uint16_t i);
  double position_of_led_center (uint32_t led_id);
  double calc_distance(double x, double y);
  uint32_t color_for_distance (double d);

private:
    uint16_t position;
};

#endif /* defined(__RNBEAM__) */