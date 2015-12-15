


void setup() {
    pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(5000);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  Serial.println("Hello");
  // put your setup code here, to run once:
//  Wire.begin();
  Serial.println("Wire begun");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);

}
