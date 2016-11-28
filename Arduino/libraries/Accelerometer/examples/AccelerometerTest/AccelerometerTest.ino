#include "Accelerometer.h"
#include <i2c_t3.h>
#include <stdint.h>
int led = 13;

void setup() {
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  Serial.begin(9600);
  delay(500);
  Serial.println("Accelerometer test");

  bool highPassFilter = false;
  initializeAccelerometer(highPassFilter);
  if (highPassFilter)
    Serial.println("Initialized accelerometer with high pass filter");
  else
    Serial.println("Initialized accelerometer without high pass filter");
  digitalWrite(led, LOW);
}



void loop() {
  float totalG;
  float directionalG[3];
  uint8_t tapSource;

  getAccelerometerData(totalG, directionalG, tapSource);
  Serial.print(totalG);
  Serial.print("  x=");
  Serial.print(directionalG[0]);
  Serial.print("  y=");
  Serial.print(directionalG[1]);
  Serial.print("  z=");
  Serial.print(directionalG[2]);
  if (tapSource)
    Serial.println(" tapped");
  Serial.println();

  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
}
