//
//  EEPROM.h
//  PachinkoTestbed
//
//  Created by Bill on 5/30/15.
//
//

#ifndef PachinkoTestbed_EEPROM_h
#define PachinkoTestbed_EEPROM_h

class EEPROM_class {
public:
    uint8_t read( int idx )              { return 0; }
    void write( int idx, uint8_t val )   {}
    //Functionality to 'get' and 'put' objects to and from EEPROM.
    template< typename T > T &get( int idx, T &t ){
        
        return t;
    }
    
    template< typename T > const T &put( int idx, const T &t ){
    
        return t;
    }
};

extern EEPROM_class EEPROM;

#endif
