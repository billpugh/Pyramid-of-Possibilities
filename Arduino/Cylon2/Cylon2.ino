#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)


#define NUM_LIGHTS 16

uint32_t pos = 500;
uint32_t maxval = 1000;
uint32_t minval = 0;
uint32_t speed = 25;
uint32_t loop_delay_in_ms = 20;
uint32_t range = maxval - minval;

double width = 150;
double damp = .7;


int8_t direction_sign = 1;
// #define SHOW_DEBUG_PIXELS

#define QDELAY 1000
#define MAGIC_NUMBER 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LIGHTS, 2, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.println(F("Setting up... delay"));
  delay(1000);
  Serial.println("Done");  
}

void loop() {

	pos += (speed * direction_sign);

	// reset position each time it exceed maxval. 
	if ( pos > maxval ) {
		pos = minval + pos % range;
	}

#if 1
	if (( pos > 900 ) &&  ( direction_sign > 0 )) {
		direction_sign = -1;
	} else if (( pos < 100 ) &&  ( direction_sign < 0 )) {
		direction_sign = 1;
		delay(QDELAY);
	}
#else
#endif



	Serial.println(pos);

	cylon_eyes(pos);

	strip.show();

	// Serial.println(pos); 
	delay(loop_delay_in_ms); 
}

uint32_t COLOR_OFF = 0;

void cylon_eyes(uint32_t pos) {

	for ( uint32_t i = 0; i < NUM_LIGHTS; i++ ) {

		double center_position = _position_of_led_center(i);
		double distance = _calc_distance(center_position, pos);
		uint32_t color = _color_for_distance(distance);


		if ( _led_is_enabled(i) ) {
			
			strip.setPixelColor(i, color);
			// Serial.println(F("START"));
			// Serial.println(pos);
			Serial.println(distance);
			// Serial.println();
			// Serial.println(color);
		} else {
			strip.setPixelColor(i, COLOR_OFF);
		}
	}
}

// Private
uint8_t _led_is_enabled (uint32_t led_id ) {
	if ( led_id < 8 + MAGIC_NUMBER && led_id > 8 - MAGIC_NUMBER ) {
		return 1;
	}
	return 0;
}

uint32_t _color_for_distance (double d) {

	uint32_t color = 0;

	if ( d > width ) {
		color = strip.Color(0, 0, 0);
	} else {
		double percent = 1 - (d / width);

		percent = percent * percent;
		color = strip.Color(percent * 255, 0, 0);
	}

	return color;
}

double _position_of_led_center (uint32_t led_id) {

	// determine percent of range that the led is located
	double i = (double)led_id / NUM_LIGHTS;
	// Serial.println(i);

	// find the position in the range
	i = i * range;
	// Serial.println(i);

	// add in the base value of range
	i += minval;
	// Serial.println(i);

	return i;
}

double _calc_distance(double x, double y) {

	double i = fabs(x-y);
	double pastmax = i - (range/2.0);

	if ( pastmax > 0.0 ) {
		i = range/2.0 - pastmax;
	}
	return i;
}