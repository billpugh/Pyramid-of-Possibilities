#include "Accelerometer.h"
#include <Adafruit_NeoPixel.h>
#include <OctoWS2811.h>
#include "RNLightsNeoPixel.h"
#include "hsv2rgb.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, 2, NEO_GRB + NEO_KHZ800);
RNLightsNeoPixel lights = RNLightsNeoPixel(strip);

double scale(int g) {
  return (log((double)g)-3.2)/3.0;
}

void foobar(char *fmt, ... ){
  char tmp[256]; // resulting string limited to 256 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 256, fmt, args);
  va_end (args);
  Serial.print(tmp);
}

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.println("Hello");

  lights.show();
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);
  delay(200);


  initializeAccelerometer();
  delay(1000);
  digitalWrite(13, LOW);
  foobar("%7s %8s %5s %s\n", "#", "g's", "Value", "num");
  for(int i = 1; i <= 4096; i*=2) 
    foobar("%7d %9f %5d %f\n", i, i/2000.0, ((int)(255*scale(i))), scale(i));
  Serial.println();
} 





int16_t baz(int16_t x) {
  if (x >= 0)
    return x;
  return -x;
}



void loop() {

  int maxG = 0;
  int16_t accelCount[3];

  for(int i = 0; i < 80; i++) {
    delay(5);
    readAccelData(accelCount);
    int totalG = 0;
    for(int i = 0; i < 3; i++) {
      totalG += baz(accelCount[i]/8);
    }
    if (totalG < 0)
      totalG = 0;
    if (maxG < totalG)
      maxG = totalG;
  }
  double value = scale(maxG);
  if (value < 0.0)
  value = 0.0;
  else if (value > 1.0)
  value = 1.0;
  

  foobar("%5d %5d\n", maxG, (int)(255*value));
  lights.shift(true);
  lights.setPixelHSV(0,230 - 230*value, 255, 255*value);
  lights.show();

}









