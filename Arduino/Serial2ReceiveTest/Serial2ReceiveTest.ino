

// RS485 on UART1
#define rxPin 9
#define txPin 10
#define	ctsPin 22
#define led 13
void setup()
{
  pinMode(led, OUTPUT);  
  Serial.begin(9600);
  Serial.println("Hello");
  pinMode(rxPin, INPUT_PULLUP);
  pinMode(txPin, OUTPUT); 
  Serial2.begin(57600); 

  // RS485 RTS handshake signal setup
  pinMode(ctsPin, OUTPUT);
  CORE_PIN22_CONFIG = PORT_PCR_MUX(3);	// Set UART1_RTS function (ALT3, see page 209)
  //	UART1_MODEM = 0x02;			// Set TXRTSE enable RTS on transmit with active LOW
  UART1_MODEM = 0x06;			// Set TXRTSE enable RTS on transmit with active HIGH
}


void loop() {
  int available = Serial2.available();
  if (available > 0) {
    digitalWrite(led, HIGH);
    Serial.print("Available: " );
    Serial.println(available);
    while (Serial2.available() > 0) {
      Serial.print((char)Serial2.read());
    }
    Serial.println();
  }


  delay(100);
  digitalWrite(led, LOW);
  delay(100);
}



