//==================================================================================//
 
#include <CAN.h>
 
 
#define TX_GPIO_NUM   17  // Connects to CTX
#define RX_GPIO_NUM   16  // Connects to CRX
 

//==================================================================================//
 
void setup() {
  Serial.begin (115200);
  while (!Serial);
  delay (1000);
 
  Serial.println ("CAN Receiver/Receiver");
 
  // Set the pins
  CAN.setPins (RX_GPIO_NUM, TX_GPIO_NUM);
 
  // start the CAN bus at 500 kbps
  if (!CAN.begin (500E3)) {
    Serial.println ("Starting CAN failed!");
    while (1);
  }
  else {
    Serial.println ("CAN Initialized");
  }
}
 
//==================================================================================//
 
void loop() {
  // canSender();
  receiveCAN();
}
 
 
//==================================================================================//
void receiveCAN() {
  if (CAN.parsePacket()) {
    int packetId = CAN.packetId();
    int packetSize = CAN.packetDlc(); // Fetch DLC (Data Length Code)

    Serial.print("Received packet with ID ");
    Serial.print(packetId);
    Serial.print(", size: ");
    Serial.print(packetSize);
    Serial.println(" bytes");

    Serial.print("Data: ");
    // Read each byte of the incoming message
    for (int i = 0; i < packetSize; i++) {
      byte receivedByte = CAN.read();
      // Print each byte in hexadecimal format with leading zero if necessary
      Serial.print(receivedByte < 0x10 ? "0" : "");
      Serial.print(receivedByte, HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}

//==================================================================================//