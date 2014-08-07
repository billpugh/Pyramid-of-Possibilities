
// Code taken from:
// http://forum.pjrc.com/threads/23570-Teensy-3-enable-Watchdog?p=33625&viewfull=1#post33625

#ifndef __RNWatchdog__
#define __RNWatchdog__

#include <stdint.h>

void createWatchdog(uint16_t ms);
// if you don't refresh the watchdog timer before it runs out, 
// the system will be rebooted

// the smallest delay needed between each refresh is 1ms. anything faster 
// and it will also reboot.
void refreshWatchdog();

#endif /* defined(__RNWatchdog__) */
