#include <Arduino.h>

void setup() {
  // put your setup code here, to run once:
  delay(200);
  Serial.begin(9600);
  Serial.println("Hello world");
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.print(millis());
 Serial.print("  ");
 
 delay(1000);
}

