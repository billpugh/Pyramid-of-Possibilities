/* Duty cycle test.
 * Pixel 0 is cycled at maximum refresh rate
 * Pixel 1 is cycled at half that rate
 * pixel 2 is cycled at half the rate of pixel 1, 
 * etc.
 */

#include <Adafruit_NeoPixel.h>

#define MARK2 1

// Pin definitions
#if MARK2
#define PIN 22
int int1Pin = 17;  // These can be changed, 2 and 3 are the Arduinos ext int pins
int int2Pin = 16;
#else
#define PIN 2
int int1Pin = 20;  // These can be changed, 2 and 3 are the Arduinos ext int pins
int int2Pin = 21;
#endif

#define LEDs 240
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDs, PIN, NEO_GRB + NEO_KHZ800);

#define brightness 80
// Set the scale below either 2, 4 or 8


const int DELAY = 0;


uint32_t BLACK = strip.Color(0, 0, 0);
uint32_t ALL = strip.Color(brightness, brightness, brightness);

unsigned long nextUpdate;

void p(char *fmt, ... ){
  char tmp[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(tmp, 128, fmt, args);
  va_end (args);
  Serial.print(tmp);
}
long refreshes = 0;
long start;



void setup()
{
  Serial.begin(115200);
  Serial.println("Hello");
  strip.begin();
  strip.show();
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH); 

  delay(1000);

  digitalWrite(13, LOW); 
  start = millis();
  nextUpdate = start + 1000;

  p("Starting duty cycle test %d ms delay\n", DELAY);
}

void loop()
{  
  int c = refreshes;

  for(int i = 0; i < 12; i++) {
    if (c&1)
      strip.setPixelColor(i, ALL);
    else 
     strip.setPixelColor(i, BLACK);
     c>>=1;
  }

  strip.show();
  refreshes++;
  long now = millis();
  if (now > nextUpdate) {
    p("%6dms, %3d Hz\n", now-start, refreshes * 1000 / (now-start));
    nextUpdate = nextUpdate + 10000;
  }
  delay(DELAY);
}






