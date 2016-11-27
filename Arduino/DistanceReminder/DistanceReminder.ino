#include <Adafruit_NeoPixel.h>
#include <Audio.h>
#include <TimeLib.h>

const int sensorPin = 16;    // select the input pin for sensor
const int sensorVpp = 15;
const int sensorGnd = 14;
const int touchPin = 17;
const int touchPin2 = 18;
const int ledPin = 13;      // on board LED
const int audioEnablePin = 8;
const int neopixelPin = 12;
const int numPixels = 1;

AudioSynthWaveformSine   sine1;          //xy=132,263
AudioEffectEnvelope      envelope1;      //xy=264,199
AudioConnection          patchCord1(sine1, envelope1);

AudioOutputAnalog        dac1;           //xy=488,208
AudioConnection          patchCord2(envelope1, dac1);

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(numPixels, neopixelPin, NEO_GRB + NEO_KHZ800);

unsigned long lastBeep = 0;
boolean beepOn = false;
void setup() {
   setSyncProvider(getTeensy3Time);
 Serial.begin(9600);
  delay(100);
  Serial.println("Hello world");
 
  if (timeStatus()!= timeSet) {
    Serial.println("Unable to sync with the RTC");
  } else {
    Serial.println("RTC has set the system time");
  }
  
  AudioMemory(10);
  sine1.amplitude(1);
  sine1.frequency(640);
  envelope1.sustain(0.8);

  pinMode(sensorGnd, OUTPUT);
  digitalWrite(sensorGnd, LOW);
  pinMode(sensorVpp, OUTPUT);
  digitalWrite(sensorVpp, HIGH);


  pinMode(audioEnablePin, OUTPUT);

  digitalWrite(audioEnablePin, HIGH);

  Serial.println("Audio initialized");
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  pixels.begin();
  pixels.setPixelColor(0, 0, 255, 0);
  pixels.show();
  Serial.println("GREEN");

  delay(250);
  pixels.setPixelColor(0, 0, 0, 0);
  pixels.show();
  Serial.println("LEDs initialized");
  digitalClockDisplay();
}

int smoothedSensorData = 30;
int skipped = 0;


void loop() {
  // read the value from the sensor:
  pixels.setPixelColor(0, 0, 0, 0);
  int sensorValue = analogRead(sensorPin);
  int touchValue = touchRead(touchPin);
  
  if (true) {

    if (sensorValue > 10 && sensorValue < 130) {
      digitalWrite(ledPin, HIGH);
      skipped = 0;
      if (sensorValue < smoothedSensorData)
        smoothedSensorData = (2 * smoothedSensorData + sensorValue + 2) / 3;
      else
        smoothedSensorData = (12 * smoothedSensorData + sensorValue + 4) / 13;

      //       Serial.print("  ");
      //       Serial.print(smoothedSensorData);

    } else {
      digitalWrite(ledPin, LOW);
      skipped++;
      if (skipped > 10)
        smoothedSensorData = 50;
    }
    //  Serial.println();
    const int good = 40;
    const int veryBad = 70;
    // < 55 -- good
    // 55 .. 60 -- marginal
    // 80+ bad

    int score = 0;
    // score 0 = green
    // score 100 = very bad

    if (skipped <= 5) {

      int r = 0;
      int g = 0;
      if (smoothedSensorData <= good) {
        score = 0;
        g = 255;
      } else if (smoothedSensorData >= veryBad) {
        r = 255;
        score = 100;
      } else {
        score = ((smoothedSensorData - good) * 100 / (veryBad - good));
        r = 255 * score / 100;
        g = 255 - r;
      }

      digitalClockDisplay();  
      Serial.print(smoothedSensorData);
      Serial.print("  ");
      Serial.print(r);
      Serial.print("  ");
      Serial.println(g);

      for (int i = 0; i < numPixels; i++)
        pixels.setPixelColor(i, r, g, 0);
    }
    pixels.show();

    unsigned long now = millis();
    const unsigned long duration = 200;
    if (beepOn) {
      if (lastBeep + duration < now) {
        beepOn = false;
        envelope1.noteOff();
      }
    } else if (score > 0 ) {
      int delay = 500 + 100000 / (score + 20);
      if (lastBeep + delay < now) {
        lastBeep = now;
        beepOn = true;
        envelope1.noteOn();
        Serial.println("beep");
      }
    }
    //   Serial.println();
  }
  delay(20);
}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}
