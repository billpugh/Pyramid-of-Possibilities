/* EEPROM Read
 *
 * Reads the value of each byte of the EEPROM and prints it 
 * to the computer.
 */

#include <EEPROM.h>
int led = 13;


void setup()
{
  delay(200);
  Serial.begin(9600);
 uint16_t value = 0;
  if (true) for(int i = 0; i < 9; i++) {
    EEPROM.put(i*2, value);
  }

}

void loop() {
  Serial.println("tick");
  uint16_t value;
  for(int i = 0; i < 9; i++) {
    EEPROM.get(i*2, value);
     Serial.print(i);
     Serial.print("\t");
     Serial.print(value, DEC);
     Serial.println();
  }
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}

