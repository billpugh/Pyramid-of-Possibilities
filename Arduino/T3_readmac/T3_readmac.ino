#include "mac.h"

void setup() {
  delay(1000);
  Serial.begin(57600);

  Serial.println("Reading MAC from hardware...");
  read_mac();

  Serial.print("MAC: ");
  print_mac();
  Serial.println();
  pinMode(13, OUTPUT); 

  Serial.print("Finished.");
}

void loop() {
  digitalWrite(13, HIGH); 
  delay(500);
  digitalWrite(13, LOW); 
  delay(500);

}


