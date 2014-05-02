
#include <Adafruit_NeoPixel.h>
#include "OctoWS2811.h"
#include <hsv2rgb.h>
#include "RNLightsOctoWS2811.h"

const int ledsPerStrip = 60;


DMAMEM uint8_t displayMemory[ledsPerStrip*24];
uint8_t drawingMemory[ledsPerStrip*24];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory);



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
  lights.setBrightness(brightness);
  lights.rotate(true);
  Serial.println(lights.show());
  brightness--;
  if (brightness < 0)
    brightness = 256;
  delay(3);
}




