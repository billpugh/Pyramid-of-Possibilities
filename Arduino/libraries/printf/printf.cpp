

#include <stdlib.h>
#include <stdio.h>
#include "Arduino.h"

void p(char *fmt, ... ){
  char tmp[256]; // resulting string limited to 256 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 256, fmt, args);
  va_end (args);
  Serial.print(tmp);
}
