
#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include "Adafruit_SleepyDog.h"

#include "Rotation.h"


void setup() {
  // Initialize serial port and circuit playground library.
  Serial.begin(115200);
  Serial.println("Circuit Playground Rotation!");
  CircuitPlayground.begin();
  setupRotation();
}

void setColor(int pix, long rgb) {
  if (pix < 0) pix += 12;
  else if (pix > 12)  pix -= 12;
  if (pix < 5)
    CircuitPlayground.setPixelColor(pix, rgb);
  else if (pix > 5 and pix < 11)
    CircuitPlayground.setPixelColor(pix - 1, rgb);
}

void loop() {
  updateRotation();

  float z = CircuitPlayground.motionZ();
  if (abs(z) > 7)
    CircuitPlayground.clearPixels();
  else {
    for (int pixel = 0; pixel < 10; pixel++) {
      int myA = pixel;
      if (myA > 4) myA++;
      float distance = fractionalRotation(avgAngle - myA / 12.0 * 2 * pi);
      if (distance < 0)
        distance = -distance;
      int g = (int)(255 - distance / pi * 1000);
      if (g < 0) g = 0;
      CircuitPlayground.strip.setPixelColor(pixel, 0, g, 0);

    }
    CircuitPlayground.strip.show();
  }
  Serial.print(avgAngle);
  Serial.print("  ");
  Serial.print(avgSpeed);
  Serial.print("  ");
  Serial.print(avgSpeed2);
  Serial.print("  ");
  Serial.print(avgActivity);
  Serial.print("  ");
  Serial.print(longAvgActivity);
  Serial.print("  ");
  Serial.println(veryLongAvgActivity);


  delay(10);


}

