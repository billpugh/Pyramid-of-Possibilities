//
//  Bell.cpp
//  PachinkoTestbed
//
//  Created by Bill on 5/17/15.
//
//

#include "Bell.h"




Bell::Bell(Adafruit_MCP23017 & io, int pin, int durationOn, int durationOff)
  : io(io), pin(pin), durationOn(durationOn), durationOff(durationOff),
    enqueued(0), on(false), timeOff(0) {

}

void Bell::begin() {
  io.pinMode(pin, OUTPUT);
  timeOff = millis();
}

void Bell::update() {
  if (on) {
    if (millis() > timeOff) {
      on = false;
      io.digitalWrite(pin, 0);
      Serial.print("Turning bell " );
      Serial.print(pin);
      Serial.println(" off");
    }
  } else if (enqueued > 0 && millis() > timeOff + durationOff) {
    on = true;
    enqueued--;
    io.digitalWrite(pin, 1);
    Serial.print("Turning bell " );
    Serial.print(pin);
    Serial.println(" on");
    timeOff = millis() + durationOn;
  }

}

void Bell::ringFor(unsigned int ms) {
    if (!on) {
        io.digitalWrite(pin, 1);
        Serial.print("Turning bell " );
        Serial.print(pin);
        Serial.println(" on");
        on = true;
    }
    enqueued = 0;
    timeOff = millis() + ms;
}
void Bell::ring(int num) {
  enqueued += num;

}
