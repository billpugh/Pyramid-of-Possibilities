/* PP0
 First version of code for LED lighting on the pyramid of possibilities.
 
 Using MMA8452Q accelerometer and neopixel lighting.
 
 Based on MMA8452Q Example Code by: Jim Lindblom
 
 Note: The MMA8452 is an I2C sensor, however this code does
 not make use of the Arduino Wire library. Because the sensor
 is not 5V tolerant, we can't use the internal pull-ups used
 by the Wire library. Instead use the included i2c.h, defs.h and types.h files.
 */


#include <Adafruit_NeoPixel.h>
#include "Accelerometer.h"

#define MARK2 1
#define PIN 2

#define FULL_STRIP 0
#if FULL_STRIP
#define LEDs 240
#define FIRST_LED 10
#define LAST_LED 228
#else
#define LEDs 24 
#define FIRST_LED 0
#define LAST_LED 23
#endif
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDs, PIN, NEO_GRB + NEO_KHZ800);

#define brightness 255

int accelCount[3];  // Stores the 12-bit signed value
float accelG[3];  // Stores the real accel value in g's
float avgG[3]; 

uint32_t RED = strip.Color(brightness, 0, 0);
uint32_t GREEN = strip.Color(0, brightness, 0);
uint32_t BLUE = strip.Color(0, 0, brightness);
uint32_t WHITE = strip.Color(brightness/3, brightness/3, brightness/3);
uint32_t YELLOW = strip.Color(brightness/2, brightness/2, 0);
uint32_t PURPLE = strip.Color(brightness/2, 0, brightness/2);
uint32_t BLACK = strip.Color(0, 0, 0);

float  l[LEDs];
float temperature = 0.0;
float averageTemperature = 0.0;
unsigned long nextUpdate;

unsigned long nextPossibleReversal;

unsigned long nextStats;
long jiggles;
long taps;
long updates;
float totalJiggle;

void p(char *fmt, ... ){
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  Serial.print(tmp);
}
byte didTap = 0;
void tap(float v) {
  if (v >= 1.0) {
    v = 1.0;
    didTap = 1;
    taps++;
  } 
  else {
    jiggles ++;
    totalJiggle += v;
  }
  int num = v*LEDs/10;
  if (num < 1)
    num = 1;
  for(int i = 0; i < num; i++) {
    setRandomPixel(v);
  }
}

void setRandomPixel(float v) {
  int pixel = random(LAST_LED+1-FIRST_LED)+FIRST_LED;
  if (l[pixel] < v)
    l[pixel] = v;
}

void showLEDs() {
  float effectiveTemperature = temperature - averageTemperature/3;
  if (effectiveTemperature < 0)
    effectiveTemperature = 0;
  else if (effectiveTemperature > 1.0)
    effectiveTemperature = 1.0;

  float minL = 2.0;
  float maxL = 0.0;
  for(int i = FIRST_LED; i <= LAST_LED; i++) {
    if (minL > l[i])
      minL = l[i];
    if (maxL < l[i])
      maxL = l[i];
  }
  if (maxL == minL)
    maxL = minL+0.1;
  //  p("temp %f %f\n", temperature, effectiveTemperature);
  if (temperature < 0.9)
    for(int i = FIRST_LED; i <= LAST_LED; i++) 
      if (l[i] == 0.0)
        strip.setPixelColor(i, 0);
      else {
        strip.setPixelColor(i, HSVtoRGB(140*effectiveTemperature*(1+l[i]), 1.0, l[i]));
      }

  else {
    float cappedTemperature = temperature;
    if (cappedTemperature > 1.0)
      cappedTemperature = 1.0;
    float r = 10*(cappedTemperature -0.9);
    for(int i = FIRST_LED; i <= LAST_LED; i++) {

      float h1 = 140*effectiveTemperature*(1+l[i]);
      float h2 = 360*(l[i]-minL)/(maxL-minL);
      float h = r*h2 + (r-1)*h1;
      strip.setPixelColor(i, HSVtoRGB(h, 1.0, l[i]));
    }
  }
  strip.show();
}

float fade(float l) {
  l = l*0.9;
  if (l < 0.001)
    return 0.0;
  return l;
}

int direction = 1;
void updateLEDs() {
  if (didTap || jiggles > 100 ) {
    temperature = temperature+0.1;
    p("Did tap %f\n", temperature);
    didTap = 0;
  } else {
    temperature = temperature + jiggles/1000.0;
  }
  if (direction > 0) {
    float p0 = l[FIRST_LED];

    for(int i = FIRST_LED+1; i <= LAST_LED; i++)
      l[i-1] = fade(l[i]);

    l[LAST_LED] = fade(p0);
  } 
  else if (direction == 0) {
    for(int i = FIRST_LED; i <= LAST_LED; i++)
      l[i] = fade(l[i]);
  } 
  else if (direction < 0) {
    float p0 = l[LAST_LED];

    for(int i = LAST_LED; i > FIRST_LED; i--)
      l[i] = fade(l[i-1]);

    l[FIRST_LED] = fade(p0);
  }
  if (millis() > nextPossibleReversal 
    && (direction == 0 
    || (temperature < 0.1 || temperature > 0.9) && random(30) == 0)) {
    if (direction == 0) 
      direction  = random(2)*2-1;
    else 
      direction = random(3)-1;
    if (direction == 0)
      nextPossibleReversal = millis() + 500;
    else
      nextPossibleReversal = millis() + 5000;
  }

  temperature = temperature*0.97;

  // at 10 updates / second, want to add 1 led to a strip of 8 every 3 seconds
  // add 1 to a strip of 240 every 2 updates
  if (random(1000) < LAST_LED - FIRST_LED+1) 
    setRandomPixel(0.5);

  if (0) {
    float maxL = 0;
    for(int i = FIRST_LED; i <= LAST_LED; i++)
      if (maxL < l[i])
        maxL = l[i];
  }
  if (averageTemperature > temperature)
    averageTemperature = temperature;
  else
    averageTemperature = (19*averageTemperature + temperature)/20;
  updates++;
  if (millis() > nextStats) {
    p("stats %2du %2dt %3dj %4f aj %4f t %4f at\n", updates, taps, jiggles, 
    totalJiggle/jiggles,  (int)(100*temperature), (int)(100*averageTemperature) );
    taps = 0;
    jiggles = 0;
    updates = 0;
    totalJiggle = 0.0;
    nextStats = millis() + 1000;
  }
}


void setup()
{
  byte c;

  for(int i = 0; i < LEDs; i++) {
    l[i] = 0;
  }

  Serial.begin(115200);
  Serial.println("Hello");
  strip.begin();
  strip.show();

  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH); 
  strip.setPixelColor(0,RED);
  strip.show();
  delay(3000);
  strip.setPixelColor(0,BLUE);
  strip.show();

  Serial.println("Ready");
  digitalWrite(13, LOW); 


  delay(1000);
  strip.setPixelColor(0,GREEN);
  strip.show();
  delay(1000);
  Serial.println("GO");
  digitalWrite(13, HIGH); 



  Serial.println("Color test");
  nextUpdate = millis() + 100;
  nextStats = nextPossibleReversal = millis() + 1000;
  for(float l = 1.0; l >= 0.0; l -= 0.05) {
    for(int i = 0; i < LEDs; i++) 
      strip.setPixelColor(i, HSVtoRGB(i*360.0/LEDs, 1.0, l));
    strip.show();
    delay(50);
  }
  for(int i = 0; i < LEDs; i++) 
    strip.setPixelColor(i, 0);
  strip.show();
  jiggles = taps = updates = 0;
  Serial.println("Color test done");
  digitalWrite(13, LOW); 
  initializeAccelerometer();

}

void loop()
{  
  static byte source;

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

    float totalDiff = 0.0;
    for (int i=0; i<3; i++) {
      accelG[i] = (float) accelCount[i]/((1<<12)/(2*SCALE));  // get actual g value, this depends on scale being set
      totalDiff += abs(accelG[i]);

    }

    if (totalDiff > 0.01) {
      tap(totalDiff/5+0.1);
      //      p("G %4f %4f %4f %4f\n", totalDiff, accelG[0], accelG[1], accelG[1]);
    }

    if(0) {
      //  tap(totalDiff);
      // Print out values

      for (int i=0; i<3; i++)
      {
        Serial.print(accelG[i], 5);  // Print g values
        Serial.print("\t\t");  // tabs in between axes

      }
      Serial.println();
    }
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
  showLEDs();

  if (millis()  > nextUpdate) {
    if (temperature > 1.0)
      nextUpdate += 40;
    else if (temperature > 0.1)
      nextUpdate += 160-120*temperature;
    else
      nextUpdate += 150 + 1/(temperature + 0.02);
    updateLEDs();
  }
  delay(1);  // Delay here for visibility
}


// This function will read the status of the tap source register.
// Print if there's been a single or double tap, and on what axis.
void tapHandler()
{
  byte source = readRegister(0x22);  // Reads the PULSE_SRC register

  tap(1.0);
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

uint32_t color(float r, float g, float b) {
  return strip.Color((int)(255*r), (int) (255*g), (int)(255*b));
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t HSVtoRGB(  float h, float s, float v )
{
  int i;
  float r,g,b;
  float f, p, q, t;
  if( s == 0 ) {
    // achromatic (grey)
    return color(v,v,v);
  }
  h /= 60;                    // sector 0 to 5
  i = floor( h );
  f = h - i;                  // factorial part of h
  p = v * ( 1 - s );
  q = v * ( 1 - s * f );
  t = v * ( 1 - s * ( 1 - f ) );
  switch( i ) {
  case 0:
    return color(v,t,p);

  case 1:
    return color(q,v,p);

  case 2:
    return color(p,v,t);

  case 3:
    return color(p,q,v);

  case 4:
    return color(t,p,v);

  case 5:
  default:
    return color(v,p,q);
  }
}
















