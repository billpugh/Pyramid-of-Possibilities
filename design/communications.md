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
* taps
* x y z accelerometer data
* 5 + 3*4 = 17 bytes

Central broadcast:

* kind (1 byte)
* length (1 byte)
* crc (1 byte)
* status (1 byte)
* current time (4 bytes)
* median activity level (4 bytes)
* program (1 byte)
* parameter length (1 byte)
* start time (4 bytes)
* parameters (<=28 bytes)
* animation (1 byte) 
* animation parameter length (1 byte)
* animation start time (4 bytes)
* animation parameters (<= 28 bytes)

* 12 bytes for header, 34 per animation



Broadcast from central:

