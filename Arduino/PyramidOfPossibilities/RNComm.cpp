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
#include "RNInfo.h"
#include "RNSerial.h"


const uint8_t MAX_LENGTH = 255;
char buffer[MAX_LENGTH];
int bufferPosition;
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
uint8_t getHeaderByte() {
    int b = Serial2.read();
    return (uint8_t) b;
}

#ifdef POP_SIMULATOR
void checkComm(RNInfo &info) {}
#else

void checkCommHead(RNInfo & info) {
    if (!dataAvailable(info, messageReceiveTime))
        return;
    info.printf("Got head of %d bytes at %d\n", Serial2.available(), messageReceiveTime);
    uint8_t k = getHeaderByte();
    while (k != 'p') {
        info.printf("Rejecting kind of %x\n", k);
        k = getHeaderByte();
        if (Serial2.available() < 3) {
            lookForData(info);
            return;
        }
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
    Serial2.readBytes(buffer, length);
    bufferPosition = 0;
    awaitingBody = false;
    lookForData(info);
    // TODO: check checksum
    info.println("got body");
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
uint32_t lastGlobalTime;
int32_t adjustmentToMillisToGetGlobal;
float medianActivityLevel;
uint8_t program;
uint8_t programSeqId;
uint32_t programStartTime;
uint8_t programParameterLength;

void initializeComm(RNInfo &info) {
    setupSerial2(constants.serial2BaudRate);
    initializeCommDaemonTimer();
}
void parseProgramMessage(RNInfo & info) {
    status = get8Bits();
    lastGlobalTime = get32Bits();
    adjustmentToMillisToGetGlobal = lastGlobalTime - messageReceiveTime;
    medianActivityLevel = getFloat();

    program = get8Bits();
    programSeqId = get8Bits();
    programStartTime = get32Bits();
    programParameterLength = get8Bits();

    info.printf("Got message at %d, program %d\n", messageReceiveTime, program);
    info.printf("local time %d, Global time %d\n",millis(), lastGlobalTime
                );
    comm_time_t sendResponseAt = messageReceiveTime + 20 + 10*info.wirePosition;
    info.printf("wirePosition %d, scheduling response for %d\n",info.wirePosition, sendResponseAt
                );
    if (!scheduleSend(info, sendResponseAt))
        info.println("Unable to schedule send");
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
            }
        }
}

#endif

