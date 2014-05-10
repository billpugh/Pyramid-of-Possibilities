
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


const int ledsPerStrip = 60;


DMAMEM uint8_t displayMemory[ledsPerStrip*24];
uint8_t drawingMemory[ledsPerStrip*24];

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory);

RNLights dots(ledsPerStrip);
RNLightsOctoWS2811 lights(leds, drawingMemory, 0);
RNCircle circle(lights, 100.0);

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

  for(int i = 0; i < 60; i++) 
    dots.setPixelColor(i, i, 0, 0);
  lights.copyPixels(dots);
  int result = lights.show();
  Serial.println(result);
  Serial.println("Lights on");
  circle.start(0, millis());

  for(int i = 0; i < 60; i++) 
    p("%d %f %f\n", i, circle.pixelX[i], circle.pixelY[i]);
  p("starting");
  digitalWrite(1, LOW);
}
int next = 0;
int brightness = 256;
void loop() {
//  dots.setBrightness(brightness);
  dots.rotate(true);
  lights.copyPixels(dots);
    unsigned long ms = millis();


  uint16_t lit = circle.update(ms);
  if (!circle.active) {
    circle.start(random(60), ms);
    if (next >= 60)
      next = 0;
    circle.hsv.h = 30+random(200);
  }
  lights.show();

  delay(30);
}




