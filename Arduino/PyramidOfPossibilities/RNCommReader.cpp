//
//  RNCommReader.cpp
//  PlatformCode
//
//  Created by Bill on 8/11/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Arduino.h"
#include "RNCommReader.h"
#include "Constants.h"
#include "RNInfo.h"

const uint8_t MAX_LENGTH = 255;
char buffer[MAX_LENGTH];
int bufferPosition;
bool awaitingBody;
uint8_t kind;
uint8_t length;
uint8_t crc;
uint32_t timeout;
uint32_t startTime;
extern volatile uint32_t rx_start_ms;

union floatRep {
    float f;
    uint32_t i;
};
uint8_t getAvailableByte() {
    int b = Serial2.read();
    return (uint8_t) b;

}
void checkCommHead() {
    if (Serial2.available() < 3)  return;
    kind = getAvailableByte();
    length = getAvailableByte();
    crc = getAvailableByte();
    startTime = rx_start_ms;
    timeout = startTime + 1000*8*(length+3)/constants.serial2BaudRate+3;
    awaitingBody = true;
}
bool checkCommBody() {
    if (Serial2.available() < length) {
        if (millis() > timeout) {
            // timeout
            while(Serial2.available()) Serial2.read();
            awaitingBody = false;
        }
        return false;
    }
    Serial2.readBytes(buffer, length);
    bufferPosition = 0;
    awaitingBody = false;
    // TODO: check checksum
    return true;

}


uint8_t get8Bits() {
    return buffer[bufferPosition++];
}

uint16_t get16Bits() {
    return get8Bits() | (get8Bits() << 8);
}

uint32_t get32Bits() {
    return  get8Bits() | (get8Bits() << 8)
    |  (get8Bits()<<16) | (get8Bits() << 24);
}


float getFloat() {
    floatRep u;
    u.i = get32Bits();
    return u.f;
}

uint8_t status;
uint32_t currentTime;
float medianActivityLevel;
uint8_t program;
uint8_t programSeqId;
uint32_t programStartTime;
uint8_t programParameterLength;



void parseProgramMessage(RNInfo & info) {
    status = get8Bits();
    currentTime = get32Bits();
    medianActivityLevel = getFloat();
    program = get8Bits();
    programSeqId = get8Bits();
    programParameterLength = get8Bits();
    startTime = get32Bits();
    info.printf("Got message, program %d\n", program);
}

void checkComm(RNInfo &info) {
    if (!awaitingBody)
        checkCommHead();
    if (awaitingBody)
        if (checkCommBody()) {

            if (kind == 'p') {
                parseProgramMessage(info);
            }
        }
    
}

