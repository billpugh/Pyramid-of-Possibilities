#include "watchdog.h"

int counter = 0;

void setup() {
  pinMode(13, OUTPUT); 
  digitalWrite(13, HIGH); 
  Serial.begin(115200);
  Serial.println("Hello");
  Serial.println(millis());
  while (!Serial) {
    delay(100);
  }
  createWatchdog(1200);
  Serial.println("Created watchdog");
  digitalWrite(13, LOW); 
}

void loop() {
  Serial.println(millis());
  if (counter++ < 10) {
    Serial.println("Refreshing watchdog");
    refreshWatchdog();
  }
  delay(100);
}





