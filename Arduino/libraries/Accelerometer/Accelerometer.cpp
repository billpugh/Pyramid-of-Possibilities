
#include "Accelerometer.h"
#include "i2c_t3.h"
#include <stdlib.h>

// The SparkFun breakout board defaults to 1, set to 0 if SA0 jumper on the bottom of the board is set
#define SA0 1
#if SA0
#define MMA8452_ADDRESS 0x1D  // SA0 is high, 0x1C if low
#else
#define MMA8452_ADDRESS 0x1C
#endif

// Set the output data rate below. Value should be between 0 and 7
const uint8_t dataRate = 0;  // 0=800Hz, 1=400, 2=200, 3=100, 4=50, 5=12.5, 6=6.25, 7=1.56

void initMMA8452(uint8_t fsr, uint8_t dataRate);

void initializeAccelerometer() {
//  Serial.println("Initializing accelerometer");
//  Wire.begin(); //Join the bus as a master
//  Serial.println("Joined bus");
//  // Set up the interrupt pins, they're set as active high, push-pull
//  pinMode(int1Pin, INPUT);
//  digitalWrite(int1Pin, LOW);
//  pinMode(int2Pin, INPUT);
//  digitalWrite(int2Pin, LOW);
//  Serial.println("Ready to read whoAmI");
//  // Read the WHO_AM_I register, this is a good test of communication
//  int c = readRegister(0x0D, 10);  // Read WHO_AM_I register
//  if (c == -1) {
//    Serial.println("timeout when reading who_am_i");
//    while (true) {
//      delay(4000);
//      Serial.println("timeout when reading who_am_i");
//    }
//  }
//
//  Serial.println("got whoami");
//  Serial.println(c, HEX);
//  if (c == 0x1A || c == 0x2A) // WHO_AM_I should be 0x1A or 0x2A
//  {  
//    initMMA8452(SCALE, dataRate);  // init the accelerometer if communication is OK
//    if (c == 0x2A) 
//      Serial.println("MMA8452Q is online...");
//    else
//      Serial.println("MMA8451Q is online...");
//  }
//  else
//  {
//    // Loop forever if communication doesn't happen
//    while(1) {
//      Serial.print("Could not connect to MMA8452Q: 0x");
//      Serial.println(c, HEX);
//      delay(1000);
//    }
//  }
}

void updateAccelerometer() {
//  float totalDiff = 0.0;
//  float accelG[3];
//  for(int i = 0; i < 3; i++)
//    accelG[i] = 0.0;
//  if (digitalRead(int1Pin)==1)  // Interrupt pin, should probably attach to interrupt function
//  {
//    readAccelData(accelG);  // Read the x/y/z adc values
//
//
//    for (int i=0; i<3; i++) 
//      totalDiff += abs(accelG[i]);
//
//  }
//  uint8_t tapValue = 0;
//  if (digitalRead(int2Pin)==1)
//  { 
//    byte source;
//    source = readRegister(0x0C);  // Read the interrupt source reg.
//    if ((source & 0x08))  // If tap register is set go check that
//      tapValue = readRegister(0x22); 
//  }
//  accelerometerCallback(totalDiff, accelG, tapValue);
}


void readAccelData(int16_t * destination)
{
  uint8_t rawData[6];  // x/y/z accel register data stored here

  readRegisters(0x01, 6, &rawData[0]);  // Read the six raw data registers into data array

  // Loop to calculate 12-bit ADC and g value for each axis
  for (int i=0; i<6; i+=2)
  {
    destination[i/2] = (rawData[i] << 8) | rawData[i+1];  // Turn the MSB and LSB into a 12-bit value
  }

}

void readAccelData(float * destination) {
  int16_t accelCount[3];
  readAccelData(accelCount);
  for(int i = 0; i < 3; i++)
    destination[i] = (float) accelCount[i]/(1<< (15 - SCALE_SHIFT));
}

// Initialize the MMA8452 registers 
// See the many application notes for more info on setting all of these registers:
// http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=MMA8452Q
// Feel free to modify any values, these are settings that work well for me.
void initMMA8452(uint8_t fsr, uint8_t dataRate)
{
  MMA8452Standby();  // Must be in standby to change registers

  uint8_t HPF_OUT = 0x10;
  // Set up the full scale range to 2, 4, or 8g.
  if ((fsr==2)||(fsr==4)||(fsr==8))
    writeRegister(0x0E,  HPF_OUT | (fsr >> 2));  
  else
    writeRegister(0x0E, HPF_OUT);

  // Setup the 3 data rate bits, from 0 to 7
  uint8_t c = readRegister(0x2A);
  c = c & ~(0x38); // clear non-datarace
  c |= 0x04; // set low noise
  if (dataRate <= 7)
    c |= (dataRate << 3);
  writeRegister(0x2A, c);

  // Set up portrait/landscap registers - 4 steps:
  // 1. Enable P/L
  // 2. Set the back/front angle trigger points (z-lock)
  // 3. Set the threshold/hysteresis angle
  // 4. Set the debouce rate
  // For more info check out this app note: http://cache.freescale.com/files/sensors/doc/app_note/AN4068.pdf
  writeRegister(0x11, 0x40);  // 1. Enable P/L
  writeRegister(0x13, 0x44);  // 2. 29deg z-lock (don't think this register is actually writable)
  writeRegister(0x14, 0x84);  // 3. 45deg thresh, 14deg hyst (don't think this register is writable either)
  writeRegister(0x12, 0x50);  // 4. debounce counter at 100ms (at 800 hz)

  /* Set up single and double tap - 5 steps:
   1. Set up single and/or double tap detection on each axis individually.
   2. Set the threshold - minimum required acceleration to cause a tap.
   3. Set the time limit - the maximum time that a tap can be above the threshold
   4. Set the pulse latency - the minimum required time between one pulse and the next
   5. Set the second pulse window - maximum allowed time between end of latency and start of second pulse
   for more info check out this app note: http://cache.freescale.com/files/sensors/doc/app_note/AN4072.pdf */
  // writeRegister(0x21, 0x7F);  // 1. enable single/double taps on all axes
  writeRegister(0x21, 0x55);  // 1. single taps only on all axes
  // writeRegister(0x21, 0x6A);  // 1. double taps only on all axes
  writeRegister(0x23, 0x01);  // 2. x thresh at 2g, multiply the value by 0.0625g/LSB to get the threshold
  writeRegister(0x24, 0x01);  // 2. y thresh at 2g, multiply the value by 0.0625g/LSB to get the threshold
  writeRegister(0x25, 0x01);  // 2. z thresh at .5g, multiply the value by 0.0625g/LSB to get the threshold
  writeRegister(0x26, 0x30);  // 3. 30ms time limit at 800Hz odr, this is very dependent on data rate, see the app note
  writeRegister(0x27, 0xA0);  // 4. 200ms (at 800Hz odr) between taps min, this also depends on the data rate
  writeRegister(0x28, 0xFF);  // 5. 318ms (max value) between taps max

  // Set up interrupt 1 and 2
  writeRegister(0x2C, 0x02);  // Active high, push-pull interrupts
  writeRegister(0x2D, 0x3D);  // DRDY, P/L and tap ints enabled
  writeRegister(0x2E, 0x01);  // DRDY on INT1, P/L and taps on INT2

  MMA8452Active();  // Set to active to start reading
}

// Sets the MMA8452 to standby mode.
// It must be in standby to change most register settings
void MMA8452Standby()
{
  uint8_t c = readRegister(0x2A);
  writeRegister(0x2A, c & ~(0x01));
}

// Sets the MMA8452 to active mode.
// Needs to be in this mode to output data
void MMA8452Active()
{
  uint8_t c = readRegister(0x2A);
  writeRegister(0x2A, c | 0x01);
}

// Read bytesToRead sequentially, starting at addressToRead into the dest byte array
void readRegisters(uint8_t addressToRead, int bytesToRead, uint8_t * dest)
{
//  Wire.beginTransmission(MMA8452_ADDRESS);
//  Wire.write(addressToRead);
//  Wire.endTransmission(I2C_NOSTOP); //endTransmission but keep the connection active
//
//  Wire.requestFrom(MMA8452_ADDRESS, bytesToRead); //Ask for bytes, once done, bus is released by default
//
//  while(Wire.available() < bytesToRead); //Hang out until we get the # of bytes we expect
//
//  for(int x = 0 ; x < bytesToRead ; x++)
//    dest[x] = Wire.read();    
}

// Read a single byte from addressToRead and return it as a byte
uint8_t readRegister(uint8_t addressToRead)
{
//  Wire.beginTransmission(MMA8452_ADDRESS);
//  Wire.write(addressToRead);
//  Wire.endTransmission(I2C_NOSTOP); //endTransmission but keep the connection active
//
//  Wire.requestFrom(MMA8452_ADDRESS, 1); //Ask for 1 byte, once done, bus is released by default
//
//  while(!Wire.available()) ; //Wait for the data to come back
//  return Wire.read(); //Return this one byte
}

// Read a single byte from addressToRead and return it as a byte, with a timeout
// return -1 on timeout
int readRegister(uint8_t addressToRead, unsigned long timeout)
{
//  Wire.beginTransmission(MMA8452_ADDRESS);
//  Wire.write(addressToRead);
//  Wire.endTransmission(I2C_NOSTOP); //endTransmission but keep the connection active
//  Serial.print("Send address to read: ");
//  Serial.println(addressToRead, HEX);
//
//  Wire.requestFrom(MMA8452_ADDRESS, 1); //Ask for 1 byte, once done, bus is released by default
//  unsigned long expires = millis() + timeout;
//  while(!Wire.available() && millis() < expires) ; //Wait for the data to come back
//  if (!Wire.available())
//    return -1;
//  return Wire.read(); //Return this one byte
}

// Writes a single byte (dataToWrite) into addressToWrite
void writeRegister(uint8_t addressToWrite, uint8_t dataToWrite)
{
//  Wire.beginTransmission(MMA8452_ADDRESS);
//  Wire.write(addressToWrite);
//  Wire.write(dataToWrite);
//  Wire.endTransmission(); //Stop transmitting
}



