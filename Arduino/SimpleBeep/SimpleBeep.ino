
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

const int audioEnablePin = 8;


AudioSynthWaveformSine   sine1;          //xy=132,263
AudioEffectEnvelope      envelope1;      //xy=264,199
AudioConnection          patchCord1(sine1, envelope1);

AudioOutputI2S        i2s1;

AudioConnection       patchCord2(envelope1, 0, i2s1, 0);
AudioConnection       patchCord3(envelope1, 0, i2s1, 1);
AudioControlSGTL5000  sgtl5000_1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  Serial.println("Hello world");
  AudioMemory(10);
  sine1.amplitude(1);
  sine1.frequency(640);
  envelope1.sustain(0.8);

  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  // sgtl5000_1.muteHeadphone();
  pinMode(audioEnablePin, OUTPUT);
  digitalWrite(audioEnablePin, HIGH);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  Serial.println("Audio initialized");
}

void loop() {
  digitalWrite(13, HIGH);
  envelope1.noteOn();
  delay(150);
  digitalWrite(13, LOW);

  envelope1.noteOff();
  delay(1000);

}
