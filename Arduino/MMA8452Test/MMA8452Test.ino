/* MMA8452QTest
 First version of code for LED lighting on the pyramid of possibilities.
 
 Using MMA8452Q accelerometer and neopixel lighting.
 
 Based on MMA8452Q Example Code by: Jim Lindblom
 
 Note: The MMA8452 is an I2C sensor, however this code does
 not make use of the Arduino Wire library. Because the sensor
 is not 5V tolerant, we can't use the internal pull-ups used
 by the Wire library. Instead use the included i2c.h, defs.h and types.h files.
 */
#include "i2c_t3.h"  // not the wire library, can't use pull-ups

// The SparkFun breakout board defaults to 1, set to 0 if SA0 jumper on the bottom of the board is set
#define SA0 1
#if SA0
#define MMA8452_ADDRESS 0x1D  // SA0 is high, 0x1C if low
#else
#define MMA8452_ADDRESS 0x1C
#endif


int int1Pin = 11;  // These can be changed, 2 and 3 are the Arduinos ext int pins
int int2Pin = 12;

// Set the scale below either 2, 4 or 8
const byte SCALE = 2;  // Sets full-scale range to +/-2, 4, or 8g. Used to calc real g values.
// Set the output data rate below. Value should be between 0 and 7
const byte dataRate = 1;  // 0=800Hz, 1=400, 2=200, 3=100, 4=50, 5=12.5, 6=6.25, 7=1.56

int accelCount[3];  // Stores the 12-bit signed value
float accelG[3];  // Stores the real accel value in g's
float avgG[3]; 

unsigned long nextUpdate;

void p(char *fmt, ... ){
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  Serial.print(tmp);
}


void setup()
{
  byte c;

  Serial.begin(115200);
  Serial.println("Hello");

  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH); 
  delay(3000);

  Serial.println("Ready");
  digitalWrite(13, LOW); 
  Wire.begin(); //Join the bus as a master

  delay(1000);
  Serial.println("GO");
  digitalWrite(13, HIGH); 
  // Set up the interrupt pins, they're set as active high, push-pull
  pinMode(int1Pin, INPUT);
  digitalWrite(int1Pin, LOW);
  pinMode(int2Pin, INPUT);
  digitalWrite(int2Pin, LOW);
  Serial.println("Set interrupt pins");
  // Read the WHO_AM_I register, this is a good test of communication
  c = readRegister(0x0D);  // Read WHO_AM_I register
  if (c == 0x2A) // WHO_AM_I should always be 0x2A
  {  
    initMMA8452(SCALE, dataRate);  // init the accelerometer if communication is OK
    Serial.println("MMA8452Q is online...");
  }
  else
  {
    // Loop forever if communication doesn't happen
    while(1) {
      Serial.print("Could not connect to MMA8452Q: 0x");
      Serial.println(c, HEX);
      delay(1000);
    }
  }
  nextUpdate = (millis()/1000) * 1000 + 1000;

  digitalWrite(13, LOW); 
  Serial.println("Starting");
}


void loop()
{  
  static byte source;
  long now = millis();
  if (now > nextUpdate) {
    p("time %d\n", now);
    nextUpdate = nextUpdate+10000;
  }
  int change = 0;
  // If int1 goes high, all data registers have new data
  if (digitalRead(int1Pin)==1)  // Interrupt pin, should probably attach to interrupt function
  {
    readAccelData(accelCount);  // Read the x/y/z adc values
    /* 
     //Below we'll print out the ADC values for acceleration
     for (int i=0; i<3; i++)
     {
     Serial.print(accelCount[i]);
     Serial.print("\t\t");
     }
     Serial.println();
     */

    // Now we'll calculate the accleration value into actual g's

    int totalDiff = 0;
    for (int i=0; i<3; i++) {
      accelG[i] = (float) accelCount[i]/((1<<12)/(2*SCALE));  // get actual g value, this depends on scale being set
      totalDiff += abs(accelCount[i]);

    }

    if (totalDiff > 50)
      p("%10d %10d\n", millis(), totalDiff);

  }

  // If int2 goes high, either p/l has changed or there's been a single/double tap
  if (digitalRead(int2Pin)==1)
  { 
    source = readRegister(0x0C);  // Read the interrupt source reg.
    if ((source & 0x10))  // If the p/l bit is set, go check those registers
      portraitLandscapeHandler();
    if ((source & 0x08))  // If tap register is set go check that
      tapHandler();
    if ((source & 0x20))  // Otherwise, if tap register is set go check that
      Serial.println("Transient");
    if ((source & 0x04))  // Otherwise, if tap register is set go check that
      Serial.println("Freefall/motion");
  }

  delay(1);  // Delay here for visibility
}

void readAccelData(int * destination)
{
  byte rawData[6];  // x/y/z accel register data stored here

  readRegisters(0x01, 6, &rawData[0]);  // Read the six raw data registers into data array

  // Loop to calculate 12-bit ADC and g value for each axis
  for (int i=0; i<6; i+=2)
  {
    destination[i/2] = ((rawData[i] << 8) | rawData[i+1]) >> 4;  // Turn the MSB and LSB into a 12-bit value
    if (rawData[i] > 0x7F)
    {  
      // If the number is negative, we have to make it so manually (no 12-bit data type)
      destination[i/2] = destination[i/2] - 0x1000;
    }
  }

}

// This function will read the status of the tap source register.
// Print if there's been a single or double tap, and on what axis.
void tapHandler()
{
  byte source = readRegister(0x22);  // Reads the PULSE_SRC register

  if ((source & 0x10)==0x10)  // If AxX bit is set
  {
    if ((source & 0x08)==0x08)  // If DPE (double puls) bit is set
      Serial.print("    Double Tap (2) on X");  // tabbing here for visibility
    else
      Serial.print("Single (1) tap on X");

    if ((source & 0x01)==0x01)  // If PoIX is set
      Serial.println(" +");
    else
      Serial.println(" -");
  }
  if ((source & 0x20)==0x20)  // If AxY bit is set
  {
    if ((source & 0x08)==0x08)  // If DPE (double puls) bit is set
      Serial.print("    Double Tap (2) on Y");
    else
      Serial.print("Single (1) tap on Y");

    if ((source & 0x02)==0x02)  // If PoIY is set
      Serial.println(" +");
    else
      Serial.println(" -");
  }
  if ((source & 0x40)==0x40)  // If AxZ bit is set
  {
    if ((source & 0x08)==0x08)  // If DPE (double puls) bit is set
      Serial.print("    Double Tap (2) on Z");
    else
      Serial.print("Single (1) tap on Z");
    if ((source & 0x04)==0x04)  // If PoIZ is set
      Serial.println(" +");
    else
      Serial.println(" -");
  }
}

// This function will read the p/l source register and
// print what direction the sensor is now facing
void portraitLandscapeHandler()
{
  byte pl = readRegister(0x10);  // Reads the PL_STATUS register
  switch((pl&0x06)>>1)  // Check on the LAPO[1:0] bits
  {
  case 0:
    Serial.print("Portrait up, ");
    break;
  case 1:
    Serial.print("Portrait Down, ");
    break;
  case 2:
    Serial.print("Landscape Right, ");
    break;
  case 3:
    Serial.print("Landscape Left, ");
    break;
  }
  if (pl&0x01)  // Check the BAFRO bit
    Serial.print("Back");
  else
    Serial.print("Front");
  if (pl&0x40)  // Check the LO bit
    Serial.print(", Z-tilt!");
  Serial.println();
}

// Initialize the MMA8452 registers 
// See the many application notes for more info on setting all of these registers:
// http://www.freescale.com/webapp/sps/site/prod_summary.jsp?code=MMA8452Q
// Feel free to modify any values, these are settings that work well for me.
void initMMA8452(byte fsr, byte dataRate)
{
  MMA8452Standby();  // Must be in standby to change registers

  byte HPF_OUT = 0x10;
  // Set up the full scale range to 2, 4, or 8g.
  if ((fsr==2)||(fsr==4)||(fsr==8))
    writeRegister(0x0E,  HPF_OUT | (fsr >> 2));  
  else
    writeRegister(0x0E, HPF_OUT);

  // Setup the 3 data rate bits, from 0 to 7
  byte c = readRegister(0x2A);
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
  byte c = readRegister(0x2A);
  writeRegister(0x2A, c & ~(0x01));
}

// Sets the MMA8452 to active mode.
// Needs to be in this mode to output data
void MMA8452Active()
{
  byte c = readRegister(0x2A);
  writeRegister(0x2A, c | 0x01);
}

// Read bytesToRead sequentially, starting at addressToRead into the dest byte array
void readRegisters(byte addressToRead, int bytesToRead, byte * dest)
{
  Wire.beginTransmission(MMA8452_ADDRESS);
  Wire.write(addressToRead);
  Wire.endTransmission(I2C_NOSTOP); //endTransmission but keep the connection active

  Wire.requestFrom(MMA8452_ADDRESS, bytesToRead); //Ask for bytes, once done, bus is released by default

  while(Wire.available() < bytesToRead); //Hang out until we get the # of bytes we expect

  for(int x = 0 ; x < bytesToRead ; x++)
    dest[x] = Wire.read();    
}

// Read a single byte from addressToRead and return it as a byte
byte readRegister(byte addressToRead)
{
  Wire.beginTransmission(MMA8452_ADDRESS);
  Wire.write(addressToRead);
  Wire.endTransmission(I2C_NOSTOP); //endTransmission but keep the connection active

  Wire.requestFrom(MMA8452_ADDRESS, 1); //Ask for 1 byte, once done, bus is released by default

  while(!Wire.available()) ; //Wait for the data to come back
  return Wire.read(); //Return this one byte
}

// Writes a single byte (dataToWrite) into addressToWrite
void writeRegister(byte addressToWrite, byte dataToWrite)
{
  Wire.beginTransmission(MMA8452_ADDRESS);
  Wire.write(addressToWrite);
  Wire.write(dataToWrite);
  Wire.endTransmission(); //Stop transmitting
}




