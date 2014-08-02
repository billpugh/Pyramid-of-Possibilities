//
//  Constants.h
//
//  Created by Danny.
//  Copyright (c) 2014 RN. All rights reserved.
//

#ifndef CONSTANTS_PYRAMID_OF_POP
#define CONSTANTS_PYRAMID_OF_POP

#define DEBUG 1

// To test without using the full strip of LEDs, uncomment the line below and set the number of LEDs you want, as well as the index of the 1st LED.
#define FULL_STRIP


// Set values for the # of LEDs and 1st LED Index
#ifdef FULL_STRIP
// DO NOT MODIFY THESE VALUES
const int LEDs = 220;
const int FIRST_LED = 15;
#else
// Modify these values for testing with a non-full strip.
const int LEDs = 60;
const int FIRST_LED = 0;
#endif

#endif /** CONSTANTS_PYRAMID_OF_POP */