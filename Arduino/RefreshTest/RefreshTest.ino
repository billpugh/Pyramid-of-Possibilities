/* Refresh test
 */

#include <Adafruit_NeoPixel.h>

#define MARK2 1

// Pin definitions
#if MARK2
#define PIN 2
int int1Pin = 17;  // These can be changed, 2 and 3 are the Arduinos ext int pins
int int2Pin = 16;
#else
#define PIN 2
int int1Pin = 20;  // These can be changed, 2 and 3 are the Arduinos ext int pins
int int2Pin = 21;
#endif

#define LEDs 240
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDs, PIN, NEO_GRB + NEO_KHZ800);

#define brightness 255
// Set the scale below either 2, 4 or 8


const int RPM = 60;
const int DELAY = 0;

uint32_t RED = strip.Color(brightness, 0, 0);
uint32_t GREEN = strip.Color(0, brightness, 0);
uint32_t BLUE = strip.Color(0, 0, brightness);
uint32_t WHITE = strip.Color(brightness/3, brightness/3, brightness/3);
uint32_t YELLOW = strip.Color(brightness/2, brightness/2, 0);
uint32_t ORANGE = strip.Color(2*brightness/3, brightness/3, 0);
uint32_t PURPLE = strip.Color(brightness/2, 0, brightness/2);
uint32_t BLACK = strip.Color(0, 0, 0);

unsigned long nextUpdate;

typedef  struct {
  int16_t x,y,z;
} 
LedPos ;

LedPos positions[LEDs];

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

int32_t distSquared(int i, int16_t x, int16_t y, int16_t z) {
  register int32_t result;
  register int32_t diff = positions[i].x - x;
  result = diff*diff;
  diff = positions[i].y - y;
  result += diff*diff;
  diff = positions[i].z - z;
  result += diff*diff;
  return result;
}
int32_t dotProduct(int i, int16_t x, int16_t y, int16_t z) {
  return ((int32_t)x) * positions[i].x
    + ((int32_t)y) * positions[i].y
    + ((int32_t)z) * positions[i].z;
}

uint16_t countWithin(int16_t distance,  int16_t x, int16_t y, int16_t z) {
  uint16_t result = 0;
  int32_t d2 = distance*distance;
  for(int i = 0; i < LEDs; i++) 
    if (distSquared(i, x, y, z) < d2)
      result++;
  return result;
}


void setup()
{

  Serial.begin(115200);
  Serial.println("Hello");
  strip.begin();
  strip.show();
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH); 

  delay(5000);

  digitalWrite(13, LOW); 
  start = millis();
  nextUpdate = start + 1000;
  for(int i = 0; i < LEDs; i++) {
    positions[i].x = random(0,20000)-10000;
    positions[i].y = random(0,20000)-10000;
    positions[i].z = random(0,20000)-10000;
  }
  uint32_t smicro = micros();
  int count = countWithin(5000, 0, 0, 0);
  uint32_t fmicro = micros();
  p("%d point within, %d usecs\n", count, fmicro-smicro);
  p("Starting refresh test, %d RPM, %d ms delay\n", RPM, DELAY);
}


int wrap(int led) {
  return led % LEDs;
}


void comet(int pos) {
  strip.setPixelColor(wrap(pos), RED);
  strip.setPixelColor(wrap(pos-1), GREEN);
  strip.setPixelColor(wrap(pos-2), BLUE);
}

void black(int pos) {
  strip.setPixelColor(wrap(pos), BLACK);
  strip.setPixelColor(wrap(pos-1), BLACK);
  strip.setPixelColor(wrap(pos-2), BLACK);
}

void loop()
{ 
  long startShow = micros();
  long pos = millis();
  pos = pos * RPM * LEDs / 60000;
  pos = pos % LEDs;

  //  p("%4d\n", pos);
  //  int c = random() % 0x0f0f0f;
  //  for(int i = 0; i < LEDs; i++) 
  //    strip.setPixelColor(i,c);
  comet(pos);
  comet(pos + LEDs/3);
  comet(pos + 2*LEDs/3);


  strip.show();
  long endShow = micros();

  refreshes++;
  long now = millis();
  if (now > nextUpdate) {
    p("%6dms, %3d Hz\n", now-start, refreshes * 1000 / (now-start));
    p("%6dus show time\n", endShow - startShow);
    nextUpdate = nextUpdate + 5000;
  }
  if (DELAY > 0) 
    delay(DELAY);
  black(pos);
  black(pos + LEDs/3);
  black(pos + 2*LEDs/3);


}
