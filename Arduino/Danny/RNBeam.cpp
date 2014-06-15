
#import "RNBeam.h"


#include <Adafruit_NeoPixel.h>		// tpdp remove depend

#define DEBUG_LED_ID 10


#pragma mark - Helper C Functions
 
void printDouble( double val, unsigned int precision){
// prints val with number of decimal places determine by precision
// NOTE: precision is 1 followed by the number of zeros for the desired number of decimial places
// example: printDouble( 3.1415, 100); // prints 3.14 (two decimal places)

    Serial.print (int(val));  //prints the int part
    Serial.print("."); // print the decimal point
    unsigned int frac;
    if(val >= 0)
        frac = (val - int(val)) * precision;
    else
        frac = (int(val)- val ) * precision;
    Serial.println(frac,DEC) ;
}

// TODO: inline
uint32_t dannyColor(uint32_t r, uint32_t g, uint32_t b) {
	return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}


#pragma mark - RNBeam

RNBeam::RNBeam() {
	position = 0;
	maxval = 240;
	range = 240;
	halfrange = 120;
	minval = 0;
	speed = 22;
	direction_sign = 1;
	width = 100;
	width_speed = 0;
	width_direction = 1;
	r = 100;
	g = 0;
	b = 200;
	min_range_of_lights_to_draw = 0;
	max_range_of_lights_to_draw = 0; 
	offset = 0;
}

RNBeam::~RNBeam() {
}

/**
returns the LED index coresponding to the given position. 
TODO: I half-assed this logic. Might have some logic bugs. Rounding direction might not be needed.
use rounding direction (as 1 or -1) to compernsate for rounding issues such as when percent = 0.99 and we want the return value to include the max LED index.
*/
uint32_t RNBeam::convertCoordinateToLED(int coordinate, int8_t roundingDirection) {
	

	// NOTE: when numLights == range, then no conversion is needed

	return coordinate;
	// coordinate = coordinate - minval;
	// float percent = (float)coordinate/(float)range;
	// int i = (int)(percent * numLights) + roundingDirection;
	// if ( i < 0 ) {
	// 	return 0;
	// } if ( i >= numLights ) {
	// 	return numLights-1;
	// }
	// return i;
}

void RNBeam::loop() {
	// position += (speed * direction_sign);
	// this->position ++;

	// // reset position each time it exceed maxval. 
	// position = position + (direction_sign * speed);
	position = ((millis() / speed)+offset) % numLights;

	// speed = (millis() / 1000) % 128;

	// TODO assuming that numLights == maxVal, and that minVal = 0

	// if ( position > maxval ) {
	// 	position = (minval + position) % range;		// modulus to calculate leftover
	// }

// DISABLING WIDTH STUFF FOR PERFORMANCE TESTING
	// width += width_speed * width_direction;
	// if ( width > 500 ) {
	// 	width_direction = -1;
	// } else if ( width <= 60 ) {
	// 	width_direction = 1;
	// }

	int min = position - width;
	int max = position + width;
	if ( min < 0 ) {
		min += range;
	}
	if ( max > maxval ) {
		max -= range;
	}

	min_range_of_lights_to_draw = this->convertCoordinateToLED(min,-1);
	max_range_of_lights_to_draw = this->convertCoordinateToLED(max,1);
 //  Serial.println(speed);
 //    Serial.println(direction_sign);
 //      Serial.println(maxval);
	// Serial.println(position);
	// Serial.println(":P");
}

/**
calculates distance between two positions. This method calculates the circular distance
*/
int RNBeam::calc_distance(int x, int y) {

	// calculate the absolute value of x-y 
	int f = 0;
	if ( x > y ) {
		f = x-y;
	} else {
		f = y-x;
	}

	// if beyond range, subtract to make within range
	int pastmax = f - halfrange;

	if ( pastmax > 0 ) {
		f = halfrange - pastmax;
	}
	return f;
}

/**
The color to show for a given distance.
*/
uint32_t RNBeam::color_for_distance (double d) {

	uint32_t color = 0;

	if ( d > width ) {
		color = dannyColor(0, 0, 0);

	} else {
		float percent = 1.0 - (d / (float)width);
		percent = percent * percent;
		color = dannyColor(percent*r, percent * g, percent * b);
	}

	return color;
}

/**
combines two colors
*/
inline void setMax(uint8_t & current, uint8_t value) {
  if (current < value)
    current = value;
}
uint32_t RNBeam::combine_colors(uint32_t a, uint32_t b) {

#if 0
	return a > b ? a : b;
#endif

	uint32_t foo = 0;
	uint32_t bar = 0;
	uint32_t newcolor = 0;

	for ( int i = 0; i < 3; i++) {
		foo = (a >> (i*8)) & 0xFF;
		bar = (b >> (i*8)) & 0xFF;

		uint32_t foobar = foo > bar ? foo : bar;
		foobar = foobar << (i*8);

		newcolor |= foobar;

	}
	return newcolor;
	// return a>b?a:b;
}

uint32_t RNBeam::drawPixel(uint16_t i) {

#if 1
	// check if pixel index is out of range (ie. we know it will return 0 for the color). If so, return 0 (no color).
	if ( max_range_of_lights_to_draw > min_range_of_lights_to_draw ) {
		if ( i < min_range_of_lights_to_draw || i > max_range_of_lights_to_draw ) {
			return 0;	// no color since it's out of range.
		}
	} else {
		if ( i > min_range_of_lights_to_draw && i < max_range_of_lights_to_draw ) {
			return 0;
		}
	}
#endif

	// double center_position = this->position_of_led_center(i);		// not need if numLights == range
	int distance = this->calc_distance((int)i, (int)position);
	uint32_t color = this->color_for_distance((double)distance);

	// if ( i == DEBUG_LED_ID ) {
	// 	Serial.print("position=");
	// 	Serial.print(position);
	// 	Serial.print("  ");
	// 	Serial.print("center=");
	// 	printDouble(center_position, 2);
	// 	Serial.print("  ");
	// 	Serial.print("distance=");
	// 	printDouble(distance, 2);
	// 	// Serial.print("  \tcolor=");
	// 	// Serial.print(color);
	// 	Serial.println(".");
	// }

	// return dannyColor(0,20,20);
	return color;
}

#pragma mark - Unused

void RNBeam::draw() {
}

/**
converts the led_id into a position. The position is the left edge of the LED (ie. no 1/2 width calculations)
*/
// bool RNChaser::update(unsigned long millis) {
double RNBeam::position_of_led_center (uint32_t led_id) {

	// determine percent of range that the led is located
	double i = (double)led_id / numLights;

	// find the position in the range
	i = i * (double)range;

	// add in the base value of range
	i += minval;

	if ( led_id == DEBUG_LED_ID ) {	
		Serial.print("i =");
		printDouble(i, 2);
		Serial.print("ledid =");
		printDouble((double)led_id, 2);
		Serial.print("numLights =");
		printDouble((double)numLights, 2);
		Serial.println(i);
	}
	
	return i;
}