



// RS485 on UART1
// RS485 on UART1
#define rxPin 9
#define txPin 10
#define	ctsPin 22
#define led 13
void setup()
{
  delay(2000);
  pinMode(led, OUTPUT);  
  Serial.begin(9600);
  Serial.println("Hello, this is Serial2TimingTest");
   pinMode(rxPin, INPUT_PULLUP);
  pinMode(txPin, OUTPUT); 
  Serial2.begin(9600); 

  // RS485 RTS handshake signal setup
  pinMode(ctsPin, OUTPUT);
  CORE_PIN22_CONFIG = PORT_PCR_MUX(3);	// Set UART1_RTS function (ALT3, see page 209)
  UART1_MODEM = 0x06;	
}


extern volatile uint32_t rx_start_ms;
uint32_t lastData = 0;
void loop() {

  int available = Serial2.available();
  if (available > 0) {
    digitalWrite(led, HIGH);
    uint32_t received_at = rx_start_ms;
    Serial.print("Available: ");
    Serial.println(available);
    Serial.print("Arrived at: ");
    Serial.println(received_at);
    Serial.print("Now at: ");
    Serial.println(millis());
    Serial.print("period: ");
    Serial.println(received_at - lastData);
    lastData = received_at;

     while  (Serial2.available() > 0) {
      Serial.print((char)Serial2.read());
    } 
   

    Serial.println();
  }


  delay(200);
  digitalWrite(led, LOW);
  delay(100);
}




