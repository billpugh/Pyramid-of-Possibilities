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
int8_t direction_sign = 1;	// -1 or 1

#define DELAY_BETWEEN_STOBES 1000	// delay in ms between strobes
uint32_t COLOR_OFF = 0;		// the color of 'off'


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LIGHTS, 2, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.println(F("Setting up... delay"));
  delay(1000);
  Serial.println("Done");  
}

void loop() {

	_update_position();
	cylon_eyes();
	strip.show();

	delay(loop_delay_in_ms); 
}

/**
Sets the LEDs for the Cylon-eyes effect based on the current position.
*/
void cylon_eyes() {

	for ( uint32_t i = 0; i < NUM_LIGHTS; i++ ) {

		// calculate the color based on the distance of the LED from the position of the strobe ('pos').
		double center_position = _position_of_led_center(i);
		double distance = _calc_distance(center_position, pos);
		uint32_t color = _color_for_distance(distance);

		// selectively ignore the color for some LEDs and just leave them turned off. Create the clipping effect
		if ( _led_is_enabled(i) ) {			
			strip.setPixelColor(i, color);

		} else {
			strip.setPixelColor(i, COLOR_OFF);	// LED off.
		}
	}
}

// Private

#define MAGIC_NUMBER 5	// the number of LEDs that will be turned on of either side of the middle LED

/**
returns whether or not a led should be turned off. This lets us create a clipping effect where the red strobe is not shown in some LEDs.
if 1 is returned always here, then all LEDs will be on.
*/
uint8_t _led_is_enabled (uint32_t led_id ) {

	if ( led_id < NUM_LIGHTS/2 + MAGIC_NUMBER && led_id > NUM_LIGHTS/2 - MAGIC_NUMBER ) {
		return 1;
	}
	return 0;
}

/**
The color to show for a given distance.
*/
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

/**
converts the led_id into a position.
*/
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

/**
calculates distance between two positions. This method calculates the circular distance.
*/
double _calc_distance(double x, double y) {

	double i = fabs(x-y);
	double pastmax = i - (range/2.0);

	if ( pastmax > 0.0 ) {
		i = range/2.0 - pastmax;
	}
	return i;
}

/**
modified the value of pos and handles direction and speed changes.
*/
void _update_position() {

	pos += (speed * direction_sign);

	// reset position each time it exceed maxval. 
	if ( pos > maxval ) {
		pos = minval + pos % range;
	}

	if (( pos > 900 ) &&  ( direction_sign > 0 )) {
		direction_sign = -1;
	} else if (( pos < 100 ) &&  ( direction_sign < 0 )) {
		direction_sign = 1;
		delay(DELAY_BETWEEN_STOBES);
	}
	// Serial.println(pos);
}