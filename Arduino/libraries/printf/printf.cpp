

#include <stdlib.h>
#include <stdio.h>
#include "Arduino.h"

void printf(char *fmt, ... ){
  char tmp[512]; // resulting string limited to 512 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 512, fmt, args);
  va_end (args);
  Serial.print(tmp);
}
