#include <Adafruit_NeoPixel.h>

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip)

static uint16_t kCountLights = 16;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(kCountLights, 2, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  
  Serial.println(F("Setting up... delay"));
  delay(1000);
  Serial.println("Done");  
}

void loop() {
//  static int counter = 0;
//  Serial.println(counter++);
  
  uint16_t endIndex = 10;
   uint32_t c = strip.Color(0, 0, 255);
   strip.setPixelColor(kCountLights-1, c);
   strip.setPixelColor(endIndex+1, c);
   dannyTest(2, 1, 0, endIndex);
//  colorWipe(strip.Color(b, 0, 0), 250); // Red  
//  delay(10);
  
//  colorWipe(strip.Color(0, 0, 255), 50); // Blue
//  rainbow(20);
//  rainbowCycle(20);
}

void effectOnPixel(uint16_t i, uint16_t width, uint16_t fade_width, uint16_t theDirection, uint16_t startIndex, uint16_t stopIndex) {
  
  uint32_t color = strip.Color(255, 0, 0);
  uint32_t debugColor = strip.Color(0, 100, 0);
  uint32_t halfColor = strip.Color(30, 0, 0);
  uint32_t off = strip.Color(0, 0, 0); 
  
//  if ( d > 0 ) {
//    for ( uint16_t j =0; j < width; j++ ) {
//      strip.setPixelColor((i + j)%kCountLights, color);
//    }
//  }


  // find lights to turn off.
  // TODO: not optimized
  for ( uint16_t i = startIndex; i <= stopIndex; i++ ) {
    strip.setPixelColor(i, off);
  }

  // find lights to turn on
  for ( uint16_t p = i; p < i+width; p++ ) {
    if ( p <= stopIndex ) {
      strip.setPixelColor(p, color);
    }
  }
  
  // find lights to be partially on
  for ( uint16_t p = i+width; p < i+width+fade_width; p++ ) {
    if ( p <= stopIndex ) {
      strip.setPixelColor(p, halfColor);
    }
  }  
  for ( uint16_t p = 1; p <= fade_width; p++ ) {
    strip.setPixelColor(i-p, halfColor);
  }
  
  
  // DEBUG ONLY
  strip.setPixelColor(i, debugColor);
  
  
//  uint16_t offIndex;
//  for ( uint16_t j = 0; j < width * theDirection; j += theDirection ) {
//      offIndex = i+j;
//  }
//  if ( i+1 <= stopIndex ) {
//    strip.setPixelColor(i+1, off);
//  }
//  strip.setPixelColor(i-1, off);
  
//  strip.setPixelColor(i+2, off);
//  strip.setPixelColor(i-2, off);
}

/**
  width: the width of the brightest section of lights.
  fade_width : the width of the half-lit lights on either side of the brightest section. can be zero.
  startIndex : lights will not go before (less than) this index.
  stopIndex : lights will not exceed beyond (greater than) this index.
*/

void dannyTest(uint16_t width, uint16_t fade_width, uint16_t startIndex, uint16_t stopIndex) {
    
  Serial.println(F("Start Cylon Effect: Width="));
  Serial.println(width);
  
  uint16_t theDirection = 1;
  uint16_t i = startIndex;
  
  while ( 1 ) {
        
    Serial.println(i); 
    effectOnPixel(i, width, fade_width, theDirection, startIndex, stopIndex);
    strip.show();
    delay(300);
        
    // adjust values of i and theDirection
    if ( i + width - 1 >= stopIndex ) {
      theDirection = -1;
      Serial.println(F("Backward"));
    }
    if ( i == 0 ) {
      theDirection = 1;
      Serial.println(F("Foreward"));
    }    
    i += theDirection;
  }
} 

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  Serial.println(F("Color Wiping..."));
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void colorAllOff() {
  Serial.println(F("Color Off..."));
  uint32_t off = strip.Color(0, 0, 0); 
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, off);
  }
  strip.show();
}

void rainbow(uint8_t wait) {
  uint16_t i, j;
//  uint8_t g, b;
    

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

