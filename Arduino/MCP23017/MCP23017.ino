#include <i2c_t3.h>
#include "Adafruit_MCP23017.h"

Adafruit_MCP23017 io;

void setup() {
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(5000);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  Serial.println("Hello");
  Serial.println(INPUT);
  Serial.println(OUTPUT);
  Serial.println(INPUT_PULLUP);
  io.begin();
  Serial.println("have begun");
  for(int i = 0; i < 6; i++) {
    io.pinMode(i, INPUT);
    io.pullUp(i, HIGH);  // turn on a 100K pullup internally
  }
  io.pinMode(10, OUTPUT);
  io.pinMode(11, OUTPUT);

  Serial.println("now ready");
}

void loop() {
  Serial.println(io.readGPIOAB()&0x2f);
  delay(100);
// put your main code here, to run repeatedly:
  digitalWrite(13, io.digitalRead(0));
  io.digitalWrite(10,0);
  io.digitalWrite(11,1);
  delay(200);
   io.digitalWrite(10,1);
  io.digitalWrite(11,0);
  delay(200);

}
