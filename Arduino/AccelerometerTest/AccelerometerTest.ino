#include "Accelerometer.h"


bool sawTap = false;
bool sawAccel = false;

void setup() {

  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  Serial.begin(115200);
  Serial.println("Hello");
  initializeAccelerometer();
  Serial.println("Ready");
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
  delay(100);
     digitalWrite(13, LOW);
  delay(100);
 
  if (sawTap) 
      digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(100);
  if (sawAccel) 
      digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);
  delay(250);
  }

}



