
#import "RNBeam.h"


#include <Adafruit_NeoPixel.h>		// tpdp remove depend

#define DEBUG_LED_ID 10
 
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

uint32_t dannyColor(uint32_t r, uint32_t g, uint32_t b) {
	return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

/**
The color to show for a given distance.
*/
/*
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
*/

RNBeam::RNBeam() {
	position = 200;
	maxval = 240;
	range = 240;
	minval = 0;
	speed = 22;
	direction_sign = 1;
	width = 100;
	width_speed = 0;
	width_direction = 1;
	r = 100;
	g = 0;
	b = 200;
}

RNBeam::~RNBeam() {
}

void RNBeam::loop() {
	// position += (speed * direction_sign);
	// this->position ++;

	// // reset position each time it exceed maxval. 
	position = position + (direction_sign * speed);
	if ( position > maxval ) {
		position = (minval + position) % range;		// modulus to calculate leftover
	}

	width += width_speed * width_direction;

	if ( width > 500 ) {
		width_direction = -1;
	} else if ( width <= 60 ) {
		width_direction = 1;
	}
 //  Serial.println(speed);
 //    Serial.println(direction_sign);
 //      Serial.println(maxval);
	// Serial.println(position);
	// Serial.println(":P");
}



/**
calculates distance between two positions. This method calculates the circular distance
*/
double RNBeam::calc_distance(double x, double y) {


	// calculate the absolute value of x-y 
	double f;
	if ( x > y ) {
		f = x-y;
	} else {
		f = y-x;
	}

	// return x - y;
// #ifdef 0
// Serial.print(x);
// Serial.print("          ");
// Serial.println(y);
// #endif
	// double i = fabs((float)x-(float)y);
	double pastmax = f - (range/2.0);

	if ( pastmax > 0.0 ) {
		f = range/2.0 - pastmax;
	}
	// return 50;
	return f;
}

/**
		// calculate the color based on the distance of the LED from the position of the strobe ('pos').
*/

// private

/**
The color to show for a given distance.
*/
uint32_t RNBeam::color_for_distance (double d) {

	uint32_t color = 0;

	if ( d > width ) {
		color = dannyColor(0, 0, 0);
	} else {
		double percent = 1.0 - (d / (float)width);

		percent = percent * percent;
		color = dannyColor(percent*r, percent * g, percent * b);

	// 	Serial.print("percent=");
	// 	Serial.print(percent);
	// 	Serial.print("  \tcolor=");
	// 	Serial.println(color);
	}

	// return dannyColor(0,50,10);

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



// uint8_t RNBeam::getPixelRed(uint16_t pixel) {
//   pixel = 3*((pixel+offset) % numPixels);
//   return pixels[pixel];
// }
// uint8_t RNBeam::getPixelGreen(uint16_t pixel)  {
//   pixel = 3*((pixel+offset) % numPixels);
//   return pixels[pixel+1];
// }

// uint8_t RNBeam::getPixelBlue(uint16_t pixel)  {
//   pixel = 3*((pixel+offset) % numPixels);
//   return pixels[pixel+2];
// }

// void RNBeam::setPixelColorMax(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue) {
//   pixel = 3*((pixel+offset) % numPixels);
//   setMax(pixels[pixel], red);
//   setMax(pixels[pixel+1], green);
//   setMax(pixels[pixel+2], blue);
// }

// void RNLights::setPixelColorMax(uint16_t pixel, uint8_t red, uint8_t green, uint8_t blue) {
//   pixel = 3*((pixel+offset) % numPixels);
//   setMax(pixels[pixel], red);
//   setMax(pixels[pixel+1], green);
//   setMax(pixels[pixel+2], blue);
// }

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


uint32_t RNBeam::drawPixel(uint16_t i) {

	double center_position = this->position_of_led_center(i);
	double distance = this->calc_distance(center_position, (double)position);
	uint32_t color = this->color_for_distance(distance);

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

void RNBeam::draw() {

	  // Serial.println("position updated");
		  // Serial.println("draw called");
}


