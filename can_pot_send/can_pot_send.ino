

#include <CAN.h>
 
#define TX_GPIO_NUM   17  // Connects to CTX
#define RX_GPIO_NUM   16  // Connects to CRX

float floatMap(float x, float in_min, float in_max, float out_min, float out_max){
  return ((x - in_min) * (out_max - out_min)/((in_max - in_min)+ out_min));
}

void setup()
{
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

void loop()
{
  int analogValue = analogRead(14);
  float voltage = floatMap(analogValue,0,4095,0,255);
  
  // // Creating a CAN message
  // CANMessage msg;
  // msg.id = 0x123; // Change the CAN ID according to your requirements
  // msg.len = 4;    // Length of the data being sent (in bytes)
  // msg.buf[0] = (uint8_t)(voltage);             // Split the float into bytes
  // msg.buf[1] = (uint8_t)(voltage >> 8);
  // msg.buf[2] = (uint8_t)(voltage >> 16);
  // msg.buf[3] = (uint8_t)(voltage >> 24);

  // // Sending the CAN message
  // if (CAN.write(msg)) {
  //   Serial.println("Message sent successfully!");
  // } else {
  //   Serial.println("Failed to send message!");
  // }

  CAN.beginPacket(0x123);
  CAN.write((uint8_t*)&voltage, sizeof(voltage));
  CAN.endPacket();

  Serial.println("-----Data Send-----");
  Serial.print("Analog: ");
  Serial.print(analogValue);
  Serial.print(", Voltage: ");
  Serial.print(voltage);
  Serial.print("\n");
  delay(1000);
}