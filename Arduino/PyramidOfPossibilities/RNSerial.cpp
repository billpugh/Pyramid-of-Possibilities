//
//  RNSerial.cpp
//
//  Copyright (c) 2014 RN. All rights reserved.
//

#include <Arduino.h>
#include "RNSerial.h"

// RS485 on UART1
#define rxPin 9
#define txPin 10
#define	ctsPin 22

void setupSerial2(int baudRate) {
#ifndef POP_SIMULATOR
  pinMode(rxPin, INPUT_PULLUP);
  pinMode(txPin, OUTPUT); 
  Serial2.begin(baudRate); 
  pinMode(ctsPin, OUTPUT);
  CORE_PIN22_CONFIG = PORT_PCR_MUX(3);	// Set UART1_RTS function (ALT3, see page 209)
  UART1_MODEM = 0x06;			// Set TXRTSE enable RTS on transmit with active HIGH
#endif
}



