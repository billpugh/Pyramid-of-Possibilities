#include <TimerThree.h>


volatile bool fired = false;
volatile bool waiting = true;
volatile unsigned long zapAt = 0;
volatile unsigned long zapCount = 0;
void zap() {
  fired = true;
  zapAt = millis();
  zapCount++;
  Timer3.stop();
}

void setup(void)
{
  delay(1000);
    Serial.begin(9600);
    Serial.println("Starting");
    Serial.println(millis());
  Timer3.initialize(15000);
  Timer3.attachInterrupt(zap); // blinkLED to run every 0.15 seconds
  Timer3.stop();
}

// The main program will print the blink count
// to the Arduino Serial Monitor
void loop(void)
{

  
  if (fired) {
    fired = false;
    Serial.println("Zap");
    Serial.println(zapAt);
    Serial.println(millis());
    waiting = false;
  }
  if (!waiting && Serial.available()) {
    Serial.read();
    
    Serial.println("Starting");
    Serial.println(millis());
    Timer3.start();
    waiting = true;
  }
  delay(100);
}
