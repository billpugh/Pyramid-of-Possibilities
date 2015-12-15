/* IRrecord (Redux)
   by: Jim Lindblom
   SparkFun Electronics
   date: October 1, 2013

   This sketch uses Ken Shirriff's *awesome* IRremote library:
       https://github.com/shirriff/Arduino-IRremote
   It's a slightly modified version of the IRrecord example that
   comes with that library.

   This sketch uses the IR receiver diode to "record" an IR code.
   Then, when triggered via a button on pin 12, it will transmit
   that IR code out of an attached IR LED on pin 3.

   Hardware setup:
     * The output of an IR Receiver Diode (38 kHz demodulating
       version) should be connected to the Arduino's pin 11.
       * The IR Receiver diode should also be powered off the
         Arduino's 5V and GND rails.
     * The anode (+, longer leg) of an IR LED should be connected to pin 3 of
       the Arduino. The cathode (-) should be connected to a 330
       Ohm resistor, which connects to ground.
     * A button should be connected to ground on one end, and pin
       12 of the Arduino on the other.

*/
#include <IRremote.h> // Include the IRremote library

/* Connect the output of the IR receiver diode to pin 11. */
int RECV_PIN = 0;
/* Initialize the irrecv part of the IRremote  library */
IRrecv irrecv(RECV_PIN);
decode_results results; // This will store our IR received codes

IRsend irsend; // Enables IR transmit on pin 3
int led = 13;

/* Storage variables for the received IR code: */
// setup() initializes serial and the Infrared receiver.
void setup()
{
  delay(200);
  Serial.begin(9600);
  Serial.println("Starting");
  irrecv.enableIRIn(); // Start the receiver
  pinMode(led, OUTPUT);

}

// loop() checks for either a button press or a received IR code.
void loop()
{
  if (irrecv.decode(&results))
  {
    gotIRCode(); // Sort out the received code
    irrecv.resume(); // re-enable receive
  }

  // If the button is pressed, and we've received a code...
  if (Serial.available() > 0)
  {

    while (Serial.available() > 0) {
      Serial.read();
    }
    Serial.println("Sending 20");
    sendIRCode(20); // Sends out our code. (See bottom of sketch).

  }
}


/** send IR code, with a value of 0-65535 */
void sendIRCode(int value)
{
  irsend.sendNEC(value, 16);
  irrecv.enableIRIn(); // Re-enable receiver
}


void gotIRCode()
{
  if (results.decode_type == NEC)
  {
    if (results.value != REPEAT) {
      Serial.print("Received RC5: ");
      Serial.println(results.value);
      digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);               // wait for a second
      digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
    }
  }
  else {
    Serial.println("Received unknown IR signal");
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(250);               // wait for a second
    digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  }

}

