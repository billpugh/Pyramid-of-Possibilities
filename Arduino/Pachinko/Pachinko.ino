#include <i2c_t3.h>
#include <EEPROM.h>
#include "Adafruit_MCP23017.h"
#include "OctoWS2811.h"
#include "FastLED.h"
#include "PachinkoMain.h"



Adafruit_MCP23017 mcp;

void setup() {
  delay(2000);
  setupMain();
  

}

void loop() {
  loopMain();
}
