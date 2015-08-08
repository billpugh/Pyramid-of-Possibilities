#include "Accelerometer.h"
#include "mac.h"
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

bool sawTap = false;
bool sawAccel = false;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(240, 2, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
  Serial.println("Hello");
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  for(int i = 0; i < 20; i++)
    strip.setPixelColor(i, strip.Color(100, 0, 0)); 
  strip.show();
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);

  initializeAccelerometer();
  for(int i = 0; i < 20; i++)
    strip.setPixelColor(i, strip.Color(100, 100, 0)); 
  strip.show();
  delay(1000);
  Serial.println("Ready");
  read_mac();
  Serial.print("MAC: ");
  print_mac();
  Serial.println();
} 

void accelerometerCallback( float totalG, 
float directionalG[3],
uint8_t source) {
  if (totalG > 0.01) {
    Serial.println(totalG);
    sawAccel = true;
  }

  if ((source & 0x10)==0x10)  // If AxX bit is set
  {
    sawTap = true;
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
    sawTap = true;
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
    sawTap = true;
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

void loop() {
  updateAccelerometer();
  if (true) {
    digitalWrite(13, HIGH);
    delay(150);
    digitalWrite(13, LOW);
    delay(150);

    if (sawTap) 
      digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(150);
    if (sawAccel) 
      digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(300);
    if (!sawTap || !sawAccel) {

      for(int i = 0; i < 10; i++) {
        updateAccelerometer();
        delay(30);
      }
    } 
    else {
      for(int i = 0; i < 20; i++)
        strip.setPixelColor(i, strip.Color(0, 100, 0));
      strip.show();
    }
  }

}







