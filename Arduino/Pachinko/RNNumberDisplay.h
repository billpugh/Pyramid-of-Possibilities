//
//  RNNumberDisplay.h
//  PachinkoTestbed
//
//  Created by Bill on 4/20/15.
//
//

#ifndef __PachinkoTestbed__RNNumberDisplay__
#define __PachinkoTestbed__RNNumberDisplay__

#include <stdio.h>
#include "RNDigit.h"

class RNNumberDisplay {
public:
    RNNumberDisplay(RNDigit & hundreds, RNDigit & tens, RNDigit & units);
    RNNumberDisplay(RNDigit & thousands, RNDigit & hundreds, RNDigit & tens, RNDigit & units);
    
    
    void setValue(int value);
    void setColor(int rgb);
    void clear();
private:
    RNDigit *thousands,*hundreds,*tens, * units ;
    int rgb;


    
};



#endif /* defined(__PachinkoTestbed__RNNumberDisplay__) */
