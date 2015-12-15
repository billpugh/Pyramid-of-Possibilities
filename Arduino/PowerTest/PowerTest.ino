
#include "led_sysdefs.h"
#include "hsv2rgb.h"
#include "Adafruit_NeoPixel.h"
#include "OctoWS2811.h"
#include "RNLightsNeoPixel.h"


#define PIN            2

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      29

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

RNLightsNeoPixel lights(pixels);

const int numSpots = 6;
const int period = 19000;

long spotStartTime[numSpots];
uint8_t spotHue[numSpots];
uint16_t spotPixel[numSpots];

unsigned int whichCycle = -1;
int led = 13;

void setup() {
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

  Serial.begin(9600);
  lights.show();
  delay(2000);
  lights.setBrightness(255);
 
  digitalWrite(led, LOW);
  lights.show();

}

void loop() {
  for(int i = 0; i < 255; i+= 10) {
    lights.setAllPixelColors(i, i, i);
    Serial.println(i);
    lights.show();
    delay(500);
  }

}
