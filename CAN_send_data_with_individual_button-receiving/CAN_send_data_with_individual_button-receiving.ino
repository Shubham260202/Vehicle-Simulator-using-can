//==================================================================================//
 
#include <CAN.h>
 
 
#define TX_GPIO_NUM   17  // Connects to CTX
#define RX_GPIO_NUM   16  // Connects to CRX
 
#define MAX_PACKET_SIZE 64  // Defines the maximum size of the receiving packet

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

    byte receivedData[MAX_PACKET_SIZE];  // Array to store the received bytes

    Serial.print("Data: ");
    // Read each byte of the incoming message
    for (int i = 0; i < packetSize; i++) {
      byte receivedByte = CAN.read();
      receivedData[i] = receivedByte; // stores the received bytes in array
      // Print each byte in hexadecimal format with leading zero if necessary
      Serial.print(receivedByte < 0x10 ? "0" : "");
      Serial.print(receivedByte, HEX);
      Serial.print(" ");
    }
    Serial.println();

    Serial.println("----------------------------------------------");
    Serial.println("Received Data: ");
    for (int i = 0; i < packetSize; i++) {
      // Serial.print(receivedData[i] < 0x10 ? "0" : "");
      Serial.print(receivedData[i], HEX);
      // Serial.print(" ");
    }
    Serial.println();

    Serial.println("----------------------------------------------");
      // Variables to store the extracted bits D0 to D7
    int D0, D1, D2, D3, D4, D5, D6, D7;

    Serial.println("Extracted bits D0 to D7:");

    // Loop through the receivedData[] array
    for (int i = 0; i < packetSize; i++) {
      // Extract the last two bits from each byte
      D0 = (receivedData[i] & 0x01) >> 0;
      D1 = (receivedData[i] & 0x02) >> 1;
      D2 = (receivedData[i] & 0x04) >> 2;
      D3 = (receivedData[i] & 0x08) >> 3;
      D4 = (receivedData[i] & 0x10) >> 4;
      D5 = (receivedData[i] & 0x20) >> 5;
      D6 = (receivedData[i] & 0x40) >> 6;
      D7 = (receivedData[i] & 0x80) >> 7;

      // Print the extracted bits
      Serial.print(D7);
      Serial.print(D6);
      Serial.print(D5);
      Serial.print(D4);
      Serial.print(D3);
      Serial.print(D2);
      Serial.print(D1);
      Serial.print(D0);
      Serial.print(" ");
    }
    Serial.println();
    Serial.println("*****************************************************************");
  }
}

//==================================================================================//