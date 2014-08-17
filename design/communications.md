# Communications protocol for the Pyramid of possibilities


Messages are sent 

All messages have the prefix:

* kind
* length
* crc

Kinds include:

* platform report
* central broadcast
* constants update


In normal operation, we do 10 communication rounds per second.



Platform report:

* kind
* length
* crc
* status
* id
* wire position
* taps
* x y z accelerometer data
* 5 + 3*4 = 17 bytes

Central broadcast:

* kind 'p' (1 byte)
* length (1 byte)
* crc (1 byte)
* status (1 byte)
* current time (4 bytes)
* median activity level (4 bytes)
* program (1 byte)
* program seq id (1 byte)
* start time (4 bytes)
* cycles at last tweak (4 bytes, float)
* tweaked at (4 bytes), relative to animation start time
* tweak value (1 byte)
* parameter length (1 byte)
* parameters (<=28 bytes)
* animations (1 byte)
* For each animation
	* animation (1 byte) 
	* animation seq id (1 byte)
	* animation start time (4 bytes)
	* animation parameter length (1 byte)
	* animation parameters (<= 28 bytes)

* 12 bytes for header, 34 per animation



Broadcast from central:

