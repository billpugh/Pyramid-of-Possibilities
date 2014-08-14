//
//  RNCommDaemon.cpp
//
//  Created by Bill on 8/12/14.
//  Copyright (c) 2014 RN. All rights reserved.
//

// Important note: For speed, all of this code assumes that the teensy millisecond
// clock can be represented with 32 bits.


#include "RNCommDaemon.h"
#include "Arduino.h"
#include "TimerThree.h"

static volatile bool waitingForReceive = true;
static volatile comm_time_t receivedAt;

static volatile bool waitingToSend = false;
static volatile comm_time_t sendAt;
static volatile comm_time_t sentAt;

static volatile char* sendBuffer;
static volatile uint8_t sendBufferSize;


// Called in an interrupt context
void commDaemonCheck() {

    if (waitingForReceive && Serial2.available() >= 3) {
        receivedAt = (comm_time_t)millis();
        waitingForReceive = false;
    }
    if (waitingToSend) {
        comm_time_t now = (comm_time_t)millis();
        if (now < sendAt)
            return;
        waitingToSend = false;
        sentAt = now;
    }
}

void initializeCommDaemonTimer() {
    Timer3.initialize(1000);
    Timer3.attachInterrupt(commDaemonCheck);
}


bool scheduleSend(RNInfo &info,
                  comm_time_t when,
                  uint8_t size, char * buffer) {
    if (waitingToSend) {
        info.println("Can't send, another send is pending");
        return false;
    }
    noInterrupts();
    sendAt = when;
    sentAt = 0;
    waitingToSend = true;
    sendBufferSize = size;
    sendBuffer = buffer;
    interrupts();
    
    return true;
}

bool dataAvailable(RNInfo &info,
                  comm_time_t &when) {

    if (waitingForReceive) return false;
    noInterrupts();
    when = receivedAt;
    interrupts();
    return true;
}

comm_time_t getSentAt() {
    noInterrupts();
    comm_time_t result = sentAt;
    interrupts();
    return result;
}
void lookForData(RNInfo &info) {

    if (waitingForReceive) {
        info.println("Warning: already waiting for data");
    }
    noInterrupts();
    waitingForReceive = true;
    interrupts();
}
