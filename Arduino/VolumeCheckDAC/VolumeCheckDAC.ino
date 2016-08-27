#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

// GUItool: begin automatically generated code
AudioSynthWaveformSine   sine1;          //xy=132,263
AudioOutputAnalog        dac1;           //xy=488,208
AudioConnection          patchCord2(sine1, dac1);

// GUItool: end automatically generated code

// GUItool: end automatically generated code

const int audioEnablePin = 14;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  Serial.println("Hello world");
  AudioMemory(10);
  sine1.amplitude(1);
  sine1.frequency(640);
  
  pinMode(audioEnablePin, OUTPUT);
  digitalWrite(audioEnablePin, HIGH);
  
   Serial.println("Audio initialized");
}

void loop() {
  delay(200);
}

