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
  double width_speed;
  int8_t width_direction;
  int8_t direction_sign;  // -1 or 1, set programatically.

  void *strip;  // Adafruit_NeoPixel 
  uint16_t numLights;

  void loop();
  void draw();
  uint32_t drawPixel(uint16_t i);
  double position_of_led_center (uint32_t led_id);
  double calc_distance(double x, double y);
  
  // color
  uint32_t color_for_distance (double d);
  uint32_t combine_colors(uint32_t a, uint32_t b);
  uint32_t r, g, b;

  uint16_t position;


  uint8_t getPixelRed(uint16_t pixel);
  uint8_t getPixelGreen(uint16_t pixel);
  uint8_t getPixelBlue(uint16_t pixel);


private:
};

#endif /* defined(__RNBEAM__) */