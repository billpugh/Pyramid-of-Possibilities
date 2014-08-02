

#include "RNGradient.h"
#include "hsv2rgb.h"

void p(char *fmt, ... ){
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  Serial.print(tmp);
}


void setup() {
  delay(2000);
  Serial.begin(115200);
  delay(2000);
  Serial.println("Gradient test");

  RNGradient gradient(1, RNGradientBounce, 0x00ffFF, 0x20ffff);
  for(int i = 0; i < 256; i++) {
    p("Gradient(%d) = %x\n", i, gradient.getColor(i));
  }
}

void loop() {
}


