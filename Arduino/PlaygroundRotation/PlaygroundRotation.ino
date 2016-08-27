
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
  double x = CircuitPlayground.motionX();
  double y = CircuitPlayground.motionY();
  double z = CircuitPlayground.motionZ();


  double a = atan2(y, x);
  int angle = (int)(a / 2 / 3.1415926 * 12 + 6);
  // Serial.println(angle);
  CircuitPlayground.clearPixels();
  setColor(angle, 0xff00);
  setColor(angle + 1, 0x7f00);
  setColor(angle + 2, 0x3f00);
 setColor(angle - 1, 0x7f00);
  setColor(angle - 2, 0x3f00);
  updateRotation();
  Serial.print(avgAngle);
  Serial.print("  ");
  Serial.print(avgSpeed);
  Serial.print("  ");
  Serial.println(avgSpeed2);
  
  delay(10);
  

}

