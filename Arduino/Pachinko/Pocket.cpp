//
//  Pocket.cpp
//
//  Created by Bill on 5/10/15.
//
//


#include "Arduino.h"
#include <stdlib.h>
#include "Pocket.h"
#include "PachinkoMain.h"
#include "hsv2rgb.h"
#include <EEPROM.h>


Pocket::Pocket(OctoWS2811 & lights, int firstPixel, Adafruit_MCP23017 &io,  int sensor, int pointValue) : lights(lights), firstPixel(firstPixel), io(io), sensor(sensor), pointValue(pointValue),
  lastTimeChanged(0), lastTimeScored(0), lastAnimationUpdate(0), pointsScoredThisGame(0), state(false) {



};


/** Return true if score detected */
bool Pocket::checkSensor() {
  unsigned long now = millis();
  if (lastTimeChanged + DEBOUNCE_TIME > now) {
    // too soon, not going to change anything
    return false;
  }
  bool sensorState = !io.digitalRead(sensor);

  bool change = false;
  if ( sensorState && !state) {
    change = true;
  }
  else if (!sensorState & state) {
    change = true;
  }

  if (change) {

    state = sensorState;
    lastTimeChanged = now;
    return state;
  } else if (state && lastTimeChanged + TOO_LONG_CLOSED_TIME < now) {
    Serial.println("Closed for too long");
    // been closed for more than 2 seconds
    // signal this somehow

  }
  return false;
}

// strips are numbered -2 ... +2
// positions are numbered 0..6

static int offsets[] = {0, 5, 11, 18, 24};


int randomPocketColor() {
  CHSV hsv;
  hsv.h = random8();
  hsv.s = 200;
  hsv.v = 200;
  CRGB rgb;
  hsv2rgb_rainbow(hsv, rgb);
  return (rgb.r << 16 ) | (rgb.g << 8) | rgb.b;

}



void Pocket::begin() {
  io.pinMode(sensor, INPUT);
  io.pullUp(sensor, INPUT_PULLUP);
  uint16_t totalPointsScored = 0;
  EEPROM.get(2 * sensor, totalPointsScored);
  Serial.print("Pocket ");
  Serial.print(sensor);
  Serial.print(" total points ");
  Serial.print(totalPointsScored);
  Serial.println();
}

int maxPos(int strip) {
  return  6 - abs(strip);
}
void Pocket::shiftUp(int fill) {
    for (int strip = -2; strip <= 2; strip++) {
        for (int pos = maxPos(strip); pos > 0; pos--) {
            int led =  getLED(strip, pos);
            if (led != -1) {
            lights.setPixel(firstPixel + led,
                            lights.getPixel(firstPixel + led-1));
            }
        }
        lights.setPixel(firstPixel + getLED(strip, 0), fill);
    }
}
void Pocket::shiftDown(int fill) {
  for (int strip = -2; strip <= 2; strip++) {
    int mPos = maxPos(strip);
    for (int pos = 0; pos < mPos; pos++)
      lights.setPixel(firstPixel + getLED(strip, pos),
                      lights.getPixel(firstPixel + getLED(strip, pos + 1)));
    lights.setPixel(firstPixel + getLED(strip, mPos), fill);
  }
}


int Pocket::getLED(int strip, int pos) {
  if (strip < -2 || strip > 2)
    return -1;
  int maxLED = 6 - abs(strip);
  if (pos < 0 || pos > maxLED)
    return -1;
  return offsets[strip + 2] + pos;
}

void Pocket::setColorAll(int rgb) {
  for (int i = 0; i < LEDS_PER_POCKET; i++)
    lights.setPixel(firstPixel + i, rgb);
}

void Pocket::disable() {
    setColorAll(0);
}
void Pocket::setColor(int strip, int pos, int rgb) {
  int pixel = getLED(strip, pos);
  if (pixel < 0) return;
  lights.setPixel(firstPixel + pixel, rgb);
}


void Pocket::gameOver() {
  uint16_t totalPointsScored = 0;
  EEPROM.get(2 * sensor, totalPointsScored);
  totalPointsScored += pointsScoredThisGame;
  pointsScoredThisGame = 0;
  EEPROM.put(2 * sensor, totalPointsScored);
  hotUntil = millis();
}

bool Pocket::isOverheated() {
    return hotUntil - millis() > OVERHEAT;
}
bool Pocket::checkAndUpdate() {

  unsigned long now = millis();

  if (pachinkoState == e_GameOver) {
    // show game over lights
    unsigned long seconds = now / 1000;
    if ((seconds & 1) == 0)
      setColorAll(0);
    else
      setColorAll(0x808080);

    return false;
  } else {
      bool scoreDetected = checkSensor();
      if (scoreDetected) {
          
          Serial.printf("Score detected on sensor %d\n", sensor);
          if (hotUntil < now)
              hotUntil = now + HOT_INCREMENT;
          else {
              hotUntil += HOT_INCREMENT;
              Serial.printf("Sensor %d is hot: %d\n",sensor, hotUntil - now);
          }
          if (hotUntil - now > OVERHEAT) {
              Serial.printf("Sensor %d is overheated: %d\n",sensor, hotUntil - now);
              hotUntil += 100;
          } else {
              lastTimeScored = now;
              pointsScoredThisGame++;
              lastAnimationUpdate = now - 1000;
              scorePoints(pointValue);
          }
      }
    if (lastAnimationUpdate + 100 < now) {
      lastAnimationUpdate = now;
      if (lastTimeScored + 2000 * pointValue > now) {
        // show score animation
        int rgb = randomPocketColor();
        shiftUp(rgb);
      } else {
        // show attract animation
        shiftDown(0x101010);
        if ((random8() % 3) == 0) {
          int strip = random(5) - 2;
          int pos = maxPos(strip);
          int rgb = randomPocketColor();
          lights.setPixel(firstPixel + getLED(strip, pos), rgb);
        }
      }
    }

    return scoreDetected;
  }

}
