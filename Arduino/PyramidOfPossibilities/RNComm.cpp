//
//  RNComm.h
//
//  Created by Bill on 8/11/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

#include "Arduino.h"
#include "RNComm.h"
#include "RNCommDaemon.h"
#include "Constants.h"
#include "PopMain.h"
#include "RNInfo.h"
#include "RNSerial.h"
#include "AnimationInfo.h"
#include "RNEEPROM.h"
#include <string.h>

const uint8_t MAX_LENGTH = 255;
char receiveBuffer[MAX_LENGTH];
int receiveBufferPosition;
char sendBuffer[MAX_LENGTH];
int sendBufferPosition;
bool awaitingBody;
uint8_t kind;
uint8_t length;
uint8_t crc;
comm_time_t timeout;
comm_time_t messageReceiveTime;


union floatRep {
    float f;
    uint32_t i;
};

#ifdef POP_SIMULATOR
void checkComm(RNInfo &info) {}
#else

uint8_t getHeaderByte() {
    int b = Serial2.read();
    return (uint8_t) b;
}

void checkCommHead(RNInfo & info) {
    if (!dataAvailable(info, messageReceiveTime))
        return;
    info.printf("Got head of %d bytes at %d\n", Serial2.available(), messageReceiveTime);
    uint8_t k = getHeaderByte();
    while (k != 'p' && kind != 'c') {
        info.printf("Rejecting kind of %x\n", k);
        if (Serial2.available() < 3) {
            lookForData(info);
            return;
        }
        k = getHeaderByte();
    }
    kind = k;
    length = getHeaderByte();
    crc = getHeaderByte();
    timeout = messageReceiveTime + 1000*8*(length+3)/constants.serial2BaudRate+3;
    awaitingBody = true;
}
bool checkCommBody(RNInfo & info) {
    int available =  Serial2.available();
    if (available < length) {
        if (millis() > timeout) {
            // timeout
            while(Serial2.available()) Serial2.read();
            awaitingBody = false;
            info.printf("body timeout, needed %d, had %d\n", length, available);
            lookForData(info);
        }
        return false;
    }
    Serial2.readBytes(receiveBuffer, length);
    receiveBufferPosition = 0;
    awaitingBody = false;
    lookForData(info);
    // TODO: check checksum
    info.println("got body");
    return true;
    
}


uint8_t get8Bits() {
    return receiveBuffer[receiveBufferPosition++];
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

void getBytes(uint8_t * dst, uint8_t sz) {
    memcpy(dst, &receiveBuffer[receiveBufferPosition], sz);
    receiveBufferPosition += sz;
}

void put8Bits(uint8_t value) {
    sendBuffer[sendBufferPosition++] = value;
}

void put16Bits(uint16_t value) {
    put8Bits(value);
    put8Bits(value>>8);
}

void put32Bits(uint32_t value) {
    put8Bits(value);
    put8Bits(value>>8);
    put8Bits(value>>16);
    put8Bits(value>>24);
}


void putFloat(float value) {
    floatRep u;
    u.f = value;
    put32Bits(u.i);
}



uint8_t status;
uint32_t lastGlobalTime;
float medianActivityLevel;



void initializeComm(RNInfo &info) {
    setupSerial2(constants.serial2BaudRate);
    initializeCommDaemonTimer();
}

void prepareReportToCentral(RNInfo &info) {
    sendBufferPosition = 0;
    put8Bits('t');
    put8Bits(0);
    put8Bits(0);
    put8Bits(0); // status
    put16Bits(info.identifier);
    put8Bits(info.wirePosition);
    put8Bits(info.getAndResetAccumulatedTaps());
    float gData[3];
    info.getAndResetAccumulatedXYZActivity(gData);
    putFloat(gData[0]);
    putFloat(gData[1]);
    putFloat(gData[2]);
    // exclude header length from packet length
    sendBuffer[1] = sendBufferPosition-3;
    info.printf("Sending ");
    for(int i = 0; i < sendBufferPosition; i++)info.printf("%2x ", sendBuffer[i]);
    info.printf("\n");
    
}

void parseProgramMessage(RNInfo & info) {
    status = get8Bits();
    lastGlobalTime = get32Bits();
    info.setGlobalMillisOffset(messageReceiveTime, lastGlobalTime);

    medianActivityLevel = getFloat();

    AnimationInfo animationStatus = AnimationInfo((AnimationEnum) get8Bits(),
                                                  get8Bits(),
                                                  get32Bits(), 0);
    animationStatus.cyclesAtLastTweak = getFloat();
    animationStatus.lastTweakAt = get32Bits();
    animationStatus.tweakValue = get8Bits();
    animationStatus.parameterLength = get8Bits();
    getBytes(animationStatus.parameters,animationStatus.parameterLength);
    
    info.printf("Got message at %d, program %d\n", messageReceiveTime, animationStatus.program);
    info.printf("local time %d, Global time %d\n",millis(), lastGlobalTime
                );
    controller->animationUpdate(animationStatus);
    
    int numEffects = get8Bits();
    for(int i = 0; i < numEffects; i++) {
        AnimationInfo animationStatus = AnimationInfo((AnimationEnum) get8Bits(),
                                                      get8Bits(),
                                                      get32Bits(), get32Bits());
        animationStatus.cyclesAtLastTweak = 0.0;
        animationStatus.lastTweakAt = 0;
        animationStatus.tweakValue = get8Bits();
        animationStatus.parameterLength = get8Bits();
        getBytes(animationStatus.parameters,animationStatus.parameterLength);
    }
    if (constants.sendReponses) {
        prepareReportToCentral(info);
        comm_time_t sendResponseAt = messageReceiveTime + 20 + 10*info.wirePosition;
        info.printf("wirePosition %d, scheduling response for %d\n",info.wirePosition, sendResponseAt
                    );

        if (!scheduleSend(info, sendResponseAt, sendBufferPosition, sendBuffer))
            info.println("Unable to schedule send");
    }
}

void parseConstantsMessage(RNInfo & info) {
    uint8_t constantsVersion = get8Bits();
    uint16_t platform = get16Bits();
    uint16_t constantsLength = length-3;
    if (constantsVersion == RNConstants::majorVersion
        && constantsLength == sizeof(RNConstants)
        && (platform == 0 || platform == info.identifier)) {
        getBytes((uint8_t *)&constants,constantsLength);
        info.printf("Got constants for platform %d, version %d.%d\n", platform, constantsVersion,
                    constants.minorVersion);
        writeConstantsToEEPROM();
        info.println("Wrote constants to EEPROM");
    }
}
comm_time_t sentAtReported = 0;

void checkComm(RNInfo &info) {
    comm_time_t sa = getSentAt();
    if (sa != 0 && sa != sentAtReported) {
        info.printf("Data sent at %d\n", sa);
        sentAtReported = sa;
    }
    if (!awaitingBody)
        checkCommHead(info);
    if (awaitingBody)
        if (checkCommBody(info)) {
            if (kind == 'p') {
                parseProgramMessage(info);
            } else if (kind == 'c') {
                parseConstantsMessage(info);
            }
        }
}

#endif

