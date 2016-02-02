#include <Adafruit_NeoPixel.h>
#include <Audio.h>
#include <Wire.h>
#include <SD.h>
#include <SPI.h>
#include <SerialFlash.h>

const int sensorPin = A0;    // select the input pin for sensor
const int touchPin = A1;
const int ledPin = 13;      // select the pin for the LED
const int audioEnablePin = 8;
const int neopixelPin = 5;
const int numPixels = 8;

AudioSynthWaveform    waveform1;
AudioOutputI2S        i2s1;
AudioConnection       patchCord1(waveform1, 0, i2s1, 0);
AudioConnection       patchCord2(waveform1, 0, i2s1, 1);
AudioControlSGTL5000  sgtl5000_1;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numPixels, neopixelPin, NEO_GRB + NEO_KHZ800);

unsigned long beepStarted = 0;
unsigned long beepEnded = 0;
void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.println("Hello world");
  AudioMemory(10);
  waveform1.begin(WAVEFORM_SINE);
  waveform1.frequency(640);
  sgtl5000_1.enable();
  sgtl5000_1.volume(1);
  pinMode(audioEnablePin, OUTPUT);
  digitalWrite(audioEnablePin, HIGH);

  Serial.println("Audio initialized");
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pinMode(neopixelPin, OUTPUT);
  pixels.begin();
  Serial.println("LEDs initialized");

}

int smoothedSensorData = 30;
int skipped = 0;
void loop() {
  // read the value from the sensor:
  int sensorValue = analogRead(sensorPin);
  int touchValue = touchRead(A1);
  pixels.clear();
  Serial.print(sensorValue);
  //  Serial.print("  ");
  //  Serial.print(touchValue);


  if (sensorValue > 20 && sensorValue < 100) {
    digitalWrite(ledPin, HIGH);
    skipped = 0;
    smoothedSensorData = (7 * smoothedSensorData + sensorValue + 4) / 8;
    Serial.print("  ");
    Serial.print(smoothedSensorData);

  } else {
    digitalWrite(ledPin, LOW);
    skipped++;
    if (skipped > 10)
      smoothedSensorData = 50;
  }

  // < 50 -- good
  // 51 .. 60 -- marginal
  // 61+ bad

  int score = 0;
  // score 0 = green
  // score 100 = very bad

  if (skipped <= 10) {

    int r = 0;
    int g = 0;
    if (smoothedSensorData < 50) {
      g = 255;
    } else if (smoothedSensorData > 70) {
      r = 255;
      score = 100;
    } else {
      g = 255 - (smoothedSensorData - 50) * 12;
      r = 255 - (70 - smoothedSensorData) * 12;
      score = (smoothedSensorData - 50) * 5;
    }

    for (int i = 0; i < 8; i++)
      pixels.setPixelColor(i, r, g, 0);
  }

  if (score > 0) {
    Serial.print("  ");
    Serial.print(score);
    Serial.print("  ");
    Serial.print(beepStarted);
    Serial.print("  ");
    Serial.print(beepEnded);
  }

  pixels.show();

  unsigned long now = millis();

  if (beepStarted > beepEnded) {
    // beep currently on
    int duration = 100 + score;
    if (score == 0) duration = 0;
    if (beepStarted + duration < now) {
      beepEnded = now;
      waveform1.amplitude(0);
    }
  } else if (score > 0) {
    // beep currently off
    int duration = 1000 - 5 * score;
    Serial.print("  -> " );
    Serial.print(beepEnded + duration);
    Serial.print(", " );
    Serial.print(now);
    if (beepEnded + duration < now) {
      beepStarted = now;
      waveform1.amplitude(1.0);
    }
  }
  Serial.println();
  delay(40);
}
