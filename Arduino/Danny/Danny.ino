#include <Adafruit_NeoPixel.h>
#include "RNBeam.h"
// #include "RNLightsNeoPixel.h"

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)


#define NUM_LIGHTS 240
#define PIN 12


uint32_t pos = 500;
uint32_t maxval = 1000;	// max position
uint32_t minval = 0;	// min position
uint32_t speed = 53;
uint32_t loop_delay_in_ms = 0;
uint32_t range = maxval - minval;
double width = 150;	// width (in same units as pos, maxval, minval) of a strobe band
int8_t direction_sign = 1;	// -1 or 1, set programatically.

// specify which LEDs are enabled for this effect. We turn some off for a clipping effect.
// int32_t min_led_enabled = 0;
// int32_t max_led_enabled = NUM_LIGHTS;
// DRLight *light;


#define DELAY_BETWEEN_STOBES 1000	// delay in ms between strobes
uint32_t COLOR_OFF = 0;		// the color of 'off'


/**********         ************/

const uint8_t numBeams = 2;
RNBeam beams[numBeams] = { 
  RNBeam(), 
  RNBeam()
};


Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LIGHTS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.begin(9600);
  Serial.println(F("Setting up... delay"));
  delay(1000);
  Serial.println("Done");


  for ( int i = 0; i < numBeams; i++ ) {
  	beams[i].numLights = NUM_LIGHTS;
  	beams[i].speed = 37;
  	if (i == 1 ) {
  		beams[i].speed = 70;
  		beams[i].r = 0;
  		beams[i].g = 255;
  		beams[i].b = 0;
  	} else {
  		beams[i].r = 255;
  		beams[i].g = 0;
  		beams[i].b = 0;
  	}
  	// beam.strip = &strip;
  	// beam.numLights = NUM_LIGHTS;
  }
}

void loop() {

// Serial.println("Iteration"); 

  for ( int i = 0; i < numBeams; i++ ) {
	beams[i].loop();
  	for ( int j = 0; j < NUM_LIGHTS; j++ ) {
	  	//RNBeam beam  = beams[i];
		uint32_t color = beams[i].drawPixel(j);
		uint32_t currentColor = strip.getPixelColor(j);
		uint32_t newColor = beams[i].combine_colors(color, currentColor);
		strip.setPixelColor(j, newColor);  		
  	}
  }	


	strip.show();
	delay(loop_delay_in_ms); 
}
