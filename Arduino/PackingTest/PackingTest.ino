

#include "printf.h"

struct foo {
  uint16_t x;
  uint16_t y;
  uint8_t z;
  uint16_t w;
};

struct foo f;




void setup() {
  Serial.begin(9600);
  delay(5000);
  p("Offsets %d %d %d %d\n", ((char*)&f.x) - ((char*)&f),
  ((char*)&f.y) - ((char*)&f),
  ((char*)&f.z) - ((char*)&f),
  ((char*)&f.w) - ((char*)&f));
  f.x = 0x0102;
  f.y = 0x0304;
  f.z = 0x05;
  f.w = 0x0607;
  char * ptr = (char *)&f;
  for(int i = 0; i < sizeof(foo); i++) {
    p(" %2x", ptr[i]);
  }
  Serial.println();
  
  
}

void loop () {
}
