
void setup() {
  Serial.begin(9600); // set up serial connection via USB at 9600 baud
  delay(500);          // delay 0.5 seconds; sometimes communication
                       // gets lost if you do it immediately after boot
  Serial.println("Hello world!");
}

void loop() {
 Serial.println(millis()); // print out the time since boot in milliseconds
 delay(1000);              // wait 1 second
}

