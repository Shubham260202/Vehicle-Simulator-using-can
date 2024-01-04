#include <CAN.h>

#define TX_GPIO_NUM   17  // Connects to CTX
#define RX_GPIO_NUM   16  // Connects to CRX

float mapFloat(uint8_t b0, uint8_t b1, uint8_t b2, uint8_t b3) {
  float result;
  uint32_t temp = (uint32_t)b0 | ((uint32_t)b1 << 8) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 24);
  memcpy(&result, &temp, sizeof(result));
  return result;
}

void setup() {
  Serial.begin(115200);

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

void loop() {
  // CAN_message_t msg;
  // CAN msg;
  if(CAN.parsePacket()){
    int packetId = CAN.packetId();
    int packetSize = CAN.packetDlc();

    byte receivedMsg[4];

    Serial.print("Received packet with ID ");
    Serial.print(packetId);
    Serial.print(", size: ");
    Serial.print(packetSize);
    Serial.println(" bytes");

    // float receivedVoltage = mapFloat(receivedMsg[0], receivedMsg[1], receivedMsg[2], receivedMsg[3]);
    for (int i = 0; i < 4; i++) {
      receivedMsg[i] = CAN.read();
    }
    float receivedVoltage;
    memcpy(&receivedVoltage, &receivedMsg, sizeof(receivedVoltage));

    int newreceivedvoltage = (int)receivedVoltage;
    // Process received voltage value
    Serial.print("Received Voltage: ");
    Serial.println(receivedVoltage);
    Serial.println(newreceivedvoltage, HEX);
  }
  // // Check if a message is available
  // if (CAN.available()) {
  //   CAN.read(msg);

  //   if (msg.id == 0x123) { // Check if the received message ID matches the expected ID
  //     if (msg.len == 4) {  // Check if the received message length is as expected
  //       float receivedVoltage = mapFloat(msg.buf[0], msg.buf[1], msg.buf[2], msg.buf[3]);

  //       // Process received voltage value
  //       Serial.print("Received Voltage: ");
  //       Serial.println(receivedVoltage);
  //       // You can now use the receivedVoltage variable in your code as needed.
  //     } else {
  //       Serial.println("Invalid message length!");
  //     }
  //   }
  // }
}
