//
//  RNNumberDisplay.cpp
//  PachinkoTestbed
//
//  Created by Bill on 4/20/15.
//
//

#include "RNNumberDisplay.h"


RNNumberDisplay::RNNumberDisplay(RNDigit & hundreds, RNDigit & tens, RNDigit & units) : thousands(0), hundreds(&hundreds),
tens(&tens), units(&units) {};
RNNumberDisplay::RNNumberDisplay(RNDigit & thousands, RNDigit & hundreds, RNDigit & tens, RNDigit & units) : thousands(&thousands), hundreds(&hundreds),tens(&tens), units(&units) {};


void RNNumberDisplay::clear() {
    units->clear();
    tens->clear();
    hundreds->clear();
    if (thousands)
        thousands->clear();
}
void RNNumberDisplay::setValue(int value) {
    int d = value % 10;
    units->setDigit(d);
    value /= 10;
    
    if (value == 0) {
        tens->clear();
    } else {
        d = value % 10;
        tens->setDigit(d);
        value /= 10;
    }
    
    if (value == 0) {
        hundreds->clear();
    } else {
        d = value % 10;
        hundreds->setDigit(d);
        value /= 10;
    }
    if (!thousands)
        return;
    
    d = value % 10;
    
    if (d == 0)
        thousands->clear();
    else
        thousands->setDigit(d);
    
}
void RNNumberDisplay::setColor(int rgb) {
    units->setColor(rgb);
    tens->setColor(rgb);
    
    hundreds->setColor(rgb);
    if (thousands) thousands->setColor(rgb);
    
    this->rgb = rgb;
}
