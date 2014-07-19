#include <OctoWS2811.h>

const int ledsPerStrip = 240;

DMAMEM int displayMemory[ledsPerStrip*6];
int drawingMemory[ledsPerStrip*6];

const int config = WS2811_GRB | WS2811_800kHz;

OctoWS2811 leds(ledsPerStrip, displayMemory, drawingMemory, config);


void setup() {
  leds.begin();
  leds.show();
  delay(2000);
  Serial.begin(115200);
  Serial.println("Starting");
}

int i = 0;
int color = 0xffffff;

void loop() {
  leds.setPixel(i, color);
  i++;
  if (i >= ledsPerStrip) {
    i = 0;
    if (color)
      color = 0;
    else
      color =  0xffffff;
    delay(1000);
  }
  leds.show();
  delay(10);
}


