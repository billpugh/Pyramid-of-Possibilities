

// RS485 on UART1
#define rxPin 9
#define txPin 10
#define	ctsPin 22
#define led 13

void setup()
{
  pinMode(led, OUTPUT);  
  pinMode(rxPin, INPUT_PULLUP);
  pinMode(txPin, OUTPUT); 
  Serial2.begin(115200); 
 //  Serial2.begin(9600); 

  delay(2000);
  Serial.begin(9600);
  Serial.println("Serial2SendTest");
  // RS485 RTS handshake signal setup
  pinMode(ctsPin, OUTPUT);
  CORE_PIN22_CONFIG = PORT_PCR_MUX(3);	// Set UART1_RTS function (ALT3, see page 209)
  UART1_MODEM = 0x06;			// Set TXRTSE enable RTS on transmit with active HIGH
}


void loop() {
  int now = millis() / 1000;
  Serial2.println(now);
  Serial.println(now);
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
  delay(500);
}



