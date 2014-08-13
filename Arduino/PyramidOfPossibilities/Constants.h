//
//  Constants.h
//
//  Created by Danny.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef CONSTANTS_PYRAMID_OF_POP
#define CONSTANTS_PYRAMID_OF_POP

#include <stdint.h>

//////////////////////////////////////////////////////////////////////////////////////////
// Defines
//////////////////////////////////////////////////////////////////////////////////////////

#define DEBUG 1
#define FULL_STRIP

// #define RN_REALLY_LONG_ANIMATIONS

// #define RN_PRINT_HEAP_SIZE
// #define RN_PRINT_BRIGHTNESS_ADJUSTMENTS


// Log if any animation takes longer than kMaxPaintDuration inside a call to paint()
#define RN_PRINT_LOG_ANIMATIONS
const unsigned long kMaxPaintDuration = 20;    // in ms.  See RN_PRINT_LOG_ANIMATIONS


struct RNConstants {

  // Set values for the # of LEDs and 1st LED Index
#ifdef FULL_STRIP
  // VALUES FOR FULL-STRIP (ie. platforms on the pyramid!)
  static const uint8_t LEDs = 220;
  const uint8_t FIRST_LED = 10;
#else
  // Modify these values for testing with a non-full strip.
  static const uint8_t LEDs = 60;
  const uint8_t FIRST_LED = 0;
#endif  /** #ifdef FULL_STRIP **/

  const uint8_t PULSE_THSX = 1;
  const uint8_t PULSE_THSY = 1;
  const uint8_t PULSE_THSZ = 1;

#ifdef RN_REALLY_LONG_ANIMATIONS
  const unsigned long animationDuration = 3600000;
#else
  const unsigned long animationDuration = 60000;
#endif

    const uint8_t brightnessChunkSize = 16;

    const uint16_t pyramidRadius = 7209;
    const uint16_t pyramidRadiusFromGround = 7796;

    const uint32_t serial2BaudRate = 38400;
    const uint32_t usbSerialBaudRate = 115200;
    const uint16_t watchdogTimeout = 10000;
    
};


const int ONBOARD_LED_PIN = 13;

const float RADIANS_IN_A_CIRCLE = 2*3.14159265359;

extern RNConstants constants;

#endif /** CONSTANTS_PYRAMID_OF_POP */

