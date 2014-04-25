
#include <Adafruit_NeoPixel.h>
#include "OctoWS2811.h"
#include <hsv2rgb.h>
#include "RNLightsOctoWS2811.h"

const int ledsPerStrip = 60;


DMAMEM uint8_t displayMemory[ledsPerStrip*24];
uint8_t drawingMemory[ledsPerStrip*24];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory);



void setPixel(uint16_t pixel, uint8_t r,  uint8_t g,  uint8_t b) {
  uint8_t *p = ( drawingMemory) + pixel  * 24;

  uint32_t color = (g << 16) | (r << 8) | b;
  uint32_t mask;
  for (mask = (1<<23) ; mask ; mask >>= 1) {
    if (color & mask) {
      *p++ = 1;
    } 
    else {
      *p++ = 0;
    }
  }

}

void setAllPixels( uint8_t r,  uint8_t g,  uint8_t b) {
  uint8_t *p = ( drawingMemory);

  uint32_t color = (g << 16) | (r << 8) | b;
  for(int i = 0; i < ledsPerStrip; i++) {
    uint32_t mask;
    for (mask = (1<<23) ; mask ; mask >>= 1) {
      if (color & mask) {
        *p++ = 1;
      } 
      else {
        *p++ = 0;
      }
    }
  }

}

RNLightsOctoWS2811 lights(leds, drawingMemory, 0);

void setup() {
  delay(2200);
  Serial.begin(115200);
  Serial.println("Started");
  delay(200);
  leds.begin();
  Serial.println("Lights started");
  Serial.println(lights.getNumPixels());
  delay(200);
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  for(int i = 0; i < 20; i++) {
    uint8_t b = 100 - i*5;
    setPixel(i, 0, 0, b);
    leds.show();
    delay(100);

  }
  for(int i = 0; i < 20; i++) {
    setPixel(i, 0, 0, 0);
    leds.show();
    delay(100);
  }
  for(int i = 0; i < 20; i++) {
    setAllPixels(0, i*5, 0);
    leds.show();
    delay(100);
  }
  for(int i = 100; i > 0; i--) {
    setAllPixels(0, i-1, 0);
    leds.show();
    delay(10);
  }
  Serial.println("Starting lights code");
  digitalWrite(1, LOW);

   for(int i = 0; i < 60; i++) 
     lights.setPixelColor(i, 4*i, 0, 0);
  int result = lights.show();
  Serial.println(result);
  Serial.println("Lights on");
  delay(1000);

  digitalWrite(1, LOW);
}

int brightness = 256;
void loop() {
  Serial.println("Loop");
  lights.setBrightness(brightness);
  lights.rotate(true);
  Serial.println(lights.show());
  brightness--;
  if (brightness < 0)
    brightness = 256;
  delay(3);
}



