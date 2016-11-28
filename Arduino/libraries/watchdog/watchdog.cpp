
// Code taken from:
// http://forum.pjrc.com/threads/23570-Teensy-3-enable-Watchdog?p=33625&viewfull=1#post33625


#include "watchdog.h"
#include <Arduino.h>

void createWatchdog(uint16_t ms) {
  // the following code should be placed at the end of setup() since the watchdog starts right after this
  noInterrupts();
  WDOG_UNLOCK = WDOG_UNLOCK_SEQ1;
  WDOG_UNLOCK = WDOG_UNLOCK_SEQ2;
  delayMicroseconds(1); // Need to wait a bit..
  WDOG_STCTRLH = 0x0001; // Enable WDG
  WDOG_TOVALL =  ms; // The next 2 lines sets the time-out value. This is the value that the watchdog timer compare itself to.
  WDOG_TOVALH = 0;
  WDOG_PRESC = 0; // This sets prescale clock so that the watchdog timer ticks at 1kHZ instead of the default 1kHZ/4 = 200 HZ
  interrupts();
}

void refreshWatchdog() {

  // use the following 4 lines to kick the dog
  noInterrupts();
  WDOG_REFRESH = 0xA602;
  WDOG_REFRESH = 0xB480;
  interrupts();
  // if you don't refresh the watchdog timer before it runs out, the system will be rebooted

}
