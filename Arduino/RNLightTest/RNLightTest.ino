
#include <Adafruit_NeoPixel.h>
#include "OctoWS2811.h"
#include <hsv2rgb.h>
#include "RNLightsOctoWS2811.h"
#include "RNCircle.h"

void p(char *fmt, ... ){
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  Serial.print(tmp);
}

const int ledsPerStrip = 240;

DMAMEM uint8_t displayMemory[ledsPerStrip*24];
uint8_t drawingMemory[ledsPerStrip*24];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory);

RNLights dots(ledsPerStrip);
RNLightsOctoWS2811 lights(leds, drawingMemory, 0);
RNCircle circle(lights, 100.0);


unsigned long next;
void setup() {
  delay(1000);
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
  next = 0;
}

int hue = 0;
void loop() {
  unsigned long ms = millis();
  if (next >= ms) {
    p("fade %d %d\n", next-ms, lights.fade(ms));
  } else {
    lights.setAllPixelHSVs(hue, 255, 255);
    hue += 16;
    if (hue > 255)
      hue = 0;
    lights.setFade(ms, 100, false);
    next = ms+6000;
    p("\nreset\n");
  }
  lights.show();

  delay(30);
}




