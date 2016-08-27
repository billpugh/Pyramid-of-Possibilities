
#include "led_sysdefs.h"
#include "hsv2rgb.h"
#include "Adafruit_NeoPixel.h"
#include "RNLightsNeoPixel.h"


#define PIN            11

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      512

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

RNLightsNeoPixel lights(pixels);

void setHSV(int x, int y, int h, int s, int v) {
  y = 31-y;
  int pixel = 16 * x;
  if (y >=16) {
    pixel += 256;
    y -=16;
  }
  if (x % 2 == 1)
    y = 15 - y;
  pixel += y;
  lights.setPixelHSV(pixel, h, s, v);
}
const int drops = 24;

int x[drops], y[drops], hue[drops];

void updateDrops() {
  for (int i = 0; i < drops; i++) {
    if (y[i] > 0) y[i]--;
    else {
      if (y[i] == -1)
        y[i] = random(10,64);
      else 
       y[i] = random(30,64);
      x[i] = random(16);
      hue[i] = random(0, 256);
    }
    if (y[i] < 32)
      setHSV(x[i], y[i], hue[i], 0, 255);
  }

}
void setup() {
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);  // enable access to LEDs
  for (int i = 0; i < drops; i++)
    y[i] = -1;
  lights.setFade(millis(), 200);
  lights.setBrightness(20);

}

void loop() {
  lights.fade(millis());
  updateDrops();
  lights.show();
  delay(100);
}
