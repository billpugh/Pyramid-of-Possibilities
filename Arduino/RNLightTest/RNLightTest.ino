
#include <Adafruit_NeoPixel.h>
#include "OctoWS2811.h"
#include <hsv2rgb.h>
#include "RNLightsOctoWS2811.h"
#include "RNCircle.h"

const int ledsPerStrip = 60;


DMAMEM uint8_t displayMemory[ledsPerStrip*24];
uint8_t drawingMemory[ledsPerStrip*24];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory);

RNLights dots(ledsPerStrip);
RNLightsOctoWS2811 lights(leds, drawingMemory, 0);
RNCircle circle(lights, 100.0);

void setup() {
  delay(2200);
  Serial.begin(115200);
  Serial.println("Started");
  delay(200);
  Serial.println("Lights started");
  Serial.println(lights.getNumPixels());
  delay(200);
  pinMode(1, OUTPUT);
  digitalWrite(1, HIGH);
  Serial.println("Starting lights code");
  digitalWrite(1, LOW);

  for(int i = 0; i < 60; i++) 
    dots.setPixelColor(i, 4*i, 0, 0);
  int result = lights.show();
  Serial.println(result);
  Serial.println("Lights on");
  delay(1000);
  circle.start(0, 100);
  digitalWrite(1, LOW);
}

int brightness = 256;
void loop() {
  dots.setBrightness(brightness);
  dots.rotate(true);
  lights.copyPixels(dots);
  if (!circle.update(millis()))
    circle.start(millis(), 0);
  Serial.println(lights.show());
  brightness--;
  if (brightness < 0)
    brightness = 256;
  delay(3);
}




