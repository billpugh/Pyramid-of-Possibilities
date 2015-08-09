/* Pachinko wireless test
   (C)2015 Alexander Griffin.  All Rights Reserved.


  Teensy 3.1 Connections   (note: this is OctoWS2811 DMA configuration)
  ----------------------
    pin 0:  UART Rx - connect to wireless data pin
    pin 3:  Reed switch input, active LOW (Do not use as PWM.  Normal use is ok.)
    pin 17: MOSFET (active high)
    pin 23: BattSense (ADC battery voltage)
Accelerometer (SCI library)
    pin 18: SDA
    pin 19: SCL
    pin 22: INT1
nRF24L01/Mirf library:
    pin 9:  CE
    pin 10: CS*
    pin 11: MISO  (connect to MOSI pin on nRF24L01 board)
    pin 12: MOSI  (connect to MISO pin on nRF24L01 board)
    pin 13: SCK
 OctoWS2811 library:
    pin 4 - Do not use
    pin 2:  LED Strip #1    OctoWS2811 drives 8 LED Strips.
    pin 14: LED strip #2    All 8 are the same length.
    pin 7:  LED strip #3
    pin 8:  LED strip #4    A 100 ohm resistor should used
    pin 6:  LED strip #5    between each Teensy pin and the
    pin 20: LED strip #6    wire to the LED strip, to minimize
    pin 21: LED strip #7    high frequency ringining & noise.
    pin 5:  LED strip #8
    pin 15 & 16 - Connect together, but do not use
*/


#include <Wire.h> // Used for I2C

#include <SPI.h>
#include <Mirf.h>
#include <nRF24L01.h>
#include <MirfHardwareSpiDriver.h>





void setup() {
        delay(500);
        Serial.begin(9600);
	// nRF24L01 / Mirf library module setup
	Mirf.cePin = 9;
	Mirf.csnPin = 10;
	Mirf.spi = &MirfHardwareSpi;
	resetTransceiver();
    Serial.println("Remote test");

	}



void loop() {
	if(readCommand()) {
		Serial.printf("***\n");
		}
	delay(100);
	}







void resetTransceiver(void)
{
	Mirf.init();
	Mirf.setRADDR((byte *)"Unit1");
	Mirf.payload = 4;
	Mirf.config();
	}


/*
 * readCommand() - Wireless (315 MHz) receiver interface
 *
 * Receiver byte format:
 *	Byte 1: Message Identifier:  0x5A
 *	Byte 2: ID/Program
 *		+-7-+-6-+-5-+-4-+-3-+-2-+-1-+-0-+
 *		| UnitID|       Program         |
 *		+-------+-----------------------+
 *	Byte 3: Checksum (sum of Byte 1 and Byte 2)
 *	Byte 4: End byte 0xFF
 *
 * In:
 *	
 * Returns:
 *	True(1)		if command received and program change is signalled
 *	False(0)	if no command received, or due to any communication error
 */


boolean readCommand(void)
{
	byte data[4];
//Serial.printf("-%02X-\n", Mirf.getStatus());


	if(!Mirf.isSending() && Mirf.dataReady()){
		Mirf.getData(data);     
		Mirf.setTADDR((byte *)"KeyPd");
//		Mirf.send(data);	//Echo data back
		Serial.printf("CMD= %02x %02x %02x %02x\n", data[0], data[1], data[2], data[3]);
			return 1;
			}

  

	return 0;
	}

