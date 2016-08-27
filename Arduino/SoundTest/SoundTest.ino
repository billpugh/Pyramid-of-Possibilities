void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
}

void loop() {
  digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  delayMicroseconds(50);               // wait for a second
  digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
  delayMicroseconds(1000); 
}
