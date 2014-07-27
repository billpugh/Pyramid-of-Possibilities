
Minimum time to update PoP LED strip: 7ms

* for 60 light strip, 2ms
* interrupts disabled for 865us
* 7 ms update time means the fastest refresh rate is 140Hz

Center/teensy Communications:

* Teensy baud rate: 115200, or 11520 bytes/second
* Choose center refresh rate: 10Hz
	* Center interval: 100ms
	* Teensy characters / interval = 1152

Central message: 256 bytes

Teensy message: 16 bytes

Central starts, lasts about 20ms

10 windows of 8 ms each, requires 2ms per message

Typical time to update animation: < 2 ms

Modify serial code to record time in ms when serial buffer goes from empty to non-empty.








