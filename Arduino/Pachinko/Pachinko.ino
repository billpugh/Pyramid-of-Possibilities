#include <i2c_t3.h>
#include <EEPROM.h>
#include "Adafruit_MCP23017.h"
#include "OctoWS2811.h"
#include "FastLED.h"
#include "PachinkoMain.h"
#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>

Adafruit_MCP23017 mcp;

void setup() {
  delay(500);
  setupMain();
}

void loop() {
  loopMain();
}
