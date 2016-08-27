#include <Adafruit_CircuitPlayground.h>
#include <Wire.h>
#include <SPI.h>
#include <math.h>
#include "Rotation.h>


float prevAngle;
float avgAngle;
float avgSpeed;
unsigned long lastMillis;
const float fractionOld = 0.8;
const unsigned long updateInterval = 50;
const float pi = 3.1415926;
const float halfPi = pi/2;

void setupRotation() {
	lastMillis = millis();
	avgSpeed = 0.0;
}

float getAngle() {
 float x = CircuitPlayground.motionX();
 float y = CircuitPlayground.motionY();
 float z = CircuitPlayground.motionZ();

 float a = atan2(y, x);
 return a;
}

float fractionalRotation(float a) {
  while (a > halfPi)
   a -= halfPi;
  while (a < -halfPi)
   a += halfPi;
  return a;
}

void updateRotation() {
  float a = getAngle();
  float diff = fractionalRotation(a - avgAngle);
  avgAngle = fractionOld * avgAngle + (1-fractionOld) * a;

  unsigned long now = millis();
  if (now > lastMillis) {
  	float speed = fractionalRotation(a - prevAngle);
	speed = speed * 1000.0 / (now - lastMillis);
	avgSpeed = fractionOld * avgSpeed + (1-fractionOld) * speed;
	}
  lastMillis = now;
}
