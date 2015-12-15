#include <stdio.h>
#include <i2c_t3.h>

const byte device = 0x20; //default addrress of IO chip

const byte GPIOA = 0x12; //IO pins, port A
const byte GPIOB = 0x13; //IO pins, port B

const byte GPPUA = 0x0C; //pull up resistors ,port A
const byte GPPUB = 0x0D; //pull up resistors ,port B

void setup() {
  digitalWrite(13, LOW);
  delay(1000);
  digitalWrite(13, HIGH);
  delay(5000);
  digitalWrite(13, LOW);
  Serial.begin(9600);
  Serial.println("Hello");
  Wire.begin();
  Serial.println("have begun");
  seti2cbyte(device, GPPUA, 0xFF); //enable pull-up resistors on port A
  seti2cbyte(device, GPPUB, 0xFF); //enable pull-up resistors on port B
  Serial.println("have set values");
}

byte geti2cbyte(byte address, byte ptr) {
  Wire.beginTransmission(address);
  Wire.write(ptr);
  Wire.endTransmission();
  Wire.requestFrom(address, 1); // request one byte of data from MCP20317
  byte inputs = Wire.read();
  return inputs;
}

void seti2cbyte(byte address, byte ptr, byte value) {
  Wire.beginTransmission(address);
  Wire.write(ptr); // set MCP23017 memory pointer to GPPUA address
  Wire.write(value); // enable pull up resistors
  Wire.endTransmission();
}

void loop() {

  byte port_a = geti2cbyte(device, GPIOA); //get status of pins 1-8
  byte port_b = geti2cbyte(device, GPIOB); //get status of pins 21-28
  Serial.println(port_a);
  Serial.println(port_b);
  Serial.println();
}



