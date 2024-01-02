/*


CAN ID ---->  CAN MESSAGE 
0x6E   ----> Brake
0x70   ----> Forward Motor
0x72   ----> Reverse Motor
0x74   ----> Throttle
0x76   ----> Right Indicator
0x78   ----> Left Indicator
0x7A   ----> Hazard
0x7C   ----> Ignition
0x7E   ----> Latch
0x80   ----> Head Lamp


Data Format: D0	D1	D2	D3	D4	D5	D6	D7

*/


#include <CAN.h>
 
#define TX_GPIO_NUM   17  // Connects to CTX
#define RX_GPIO_NUM   16  // Connects to CRX

// Button Used in ESP32
/*
Note:-Change the Pin No as per requirements 
*/
const int BRAKE                 = 35;
// const int FORWARD_MOTOR         = 35;
// const int REVERSE_MOTOR         = 35;
// const int THROTTLE              = 35;
const int RIGHT_INDICATOR       = 32;
const int LEFT_INDICATOR        = 33;
const int HAZARD                = 25;
const int IGNITION              = 26;
const int LATCH                 = 5;
const int HEAD_LAMP             = 18;
// const int USER_BTN              = 35;

byte sendData[][8] = {
    {0xF4,	0xFF,	0xFF,	0x4F,	0xFF,	0xFF,	0xF1,	0xFF}, // 0. Data for ID Brake 
    {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17},  // 1. Data for ID Forward Motor             - to be added
    {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27},  // 2. Data for ID Reverse Motor             - to be added
    {0x03, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07},  // 3. Data for ID Throttle                  - to be added
    {0xFF,	0xF4,	0xFF,	0xFF, 0xFF,	0xFF,	0xFF,	0xFF}, // 4. Data for ID Right Indicator
    {0xFF,	0xFF,	0xF4,	0xFF,	0xFF,	0x2F,	0xFF,	0xFF}, // 5. Data for ID Left Indicator
    {0xF2,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0x8F}, // 6. Data for ID Hazard
    {0xFF,	0xFF,	0xFF,	0xF4,	0xFF,	0xFF,	0xF4,	0xFF}, // 7. Data for ID Ignition
    {0x1F,	0xFF,	0xFF,	0xFF,	0x2F,	0xFF,	0xFF,	0xFF}, // 8. Data for Latch
    {0xFF,	0xFF,	0xFF,	0x4F,	0xFF,	0x1F,	0xFF,	0xFF}, // 9. Data for Head Lamp
  };
 
 
struct canMessage {
  char msgid;
  char msgname[30];
};

 
struct canMessage messages[] ={
  {0x6E, "Brake"},
  {0x70, "Forward Motor"},
  {0x72, "Reverse Motor"},
  {0x74, "Throttle"},
  {0x76, "Right Indicator"},
  {0x78, "Left Indicator"},
  {0x7A, "Hazard"},
  {0x7C, "Ignition"},
  {0x7E, "Latch"},
  {0x80, "Head Lamp"}
};
 
const int noofMessages = sizeof(messages)/sizeof(messages[0]);

const int sendDataSize = (sizeof(sendData[0])/sizeof(sendData[0][0]));
void sendMessage(int x)
{

  char canID = messages[x].msgid;
  byte* canData =  sendData[x];
  sendArray(canData, sendDataSize, canID); // Sending array1 with ID 0x123
  Serial.println("CAN ID: ");
  Serial.println(canID);
  Serial.println("CAN DATA LENGTH: ");
  Serial.println(sendDataSize);
  Serial.println("CAN DATA: ");
  for (int j = 0; j < sendDataSize; j++) {
    Serial.print(canData[j], HEX); // Print data in hexadecimal format
    Serial.print(" ");
  }
  Serial.println();
}
 
void setup() {
  Serial.begin(115200);

  pinMode(BRAKE, INPUT);
  // pinMode(FORWARD_MOTOR, INPUT);
  // pinMode(REVERSE_MOTOR, INPUT);
  // pinMode(THROTTLE, INPUT);
  pinMode(RIGHT_INDICATOR, INPUT);
  pinMode(LEFT_INDICATOR, INPUT);
  pinMode(HAZARD, INPUT);
  pinMode(IGNITION, INPUT);
  pinMode(LATCH, INPUT);
  pinMode(HEAD_LAMP, INPUT);

  while (!Serial);
  delay(1000);
 
  Serial.println("CAN Receiver/Receiver");
 
  CAN.setPins(RX_GPIO_NUM, TX_GPIO_NUM);
 
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
  else {
    Serial.println("CAN Initialized");
  }
}
 
void loop() {
  // Initializing Button
  int BRAKE_BTN                 = digitalRead(BRAKE);
  // int FORWARD_MOTOR_BTN         = digitalRead(FORWARD_MOTOR);
  // int REVERSE_MOTOR_BTN         = digitalRead(REVERSE_MOTOR);
  // int THROTTLE                  = digitalRead(THROTTLE);
  int RIGHT_INDICATOR_BTN       = digitalRead(RIGHT_INDICATOR );
  int LEFT_INDICATOR_BTN        = digitalRead(LEFT_INDICATOR );
  int HAZARD_BTN                = digitalRead(HAZARD);
  int IGNITION_BTN              = digitalRead(IGNITION);
  int LATCH_BTN                 = digitalRead(LATCH);
  int HEAD_LAMP_BTN             = digitalRead(HEAD_LAMP);


  // Logic for Brake
  if(BRAKE_BTN == HIGH)
  {
    sendMessage(0);
    Serial.println("CAN MESSAGE FOR BRAKE SEND SUCCESFULLY");
  }
  // else{
  //   Serial.println("ERROR IN SENDING BRAKE CAN MESSAGE");
  //   delay(5000);
  // }

  // Logic for Right Indicator
  if(RIGHT_INDICATOR_BTN == HIGH)
  {
    sendMessage(4);
    Serial.println("CAN MESSAGE FOR RIGHT INDICATOR SEND SUCCESFULLY");
  }
  // else{
  //   Serial.println("ERROR IN SENDING RIGHT INDICATOR CAN MESSAGE");
  //   delay(5000);
  // }

  // Logic for Left Indicator
  if(LEFT_INDICATOR_BTN == HIGH)
  {
    sendMessage(5);
    Serial.println("CAN MESSAGE FOR LEFT INDICATOR SEND SUCCESFULLY");
  }
  // else{
  //   Serial.println("ERROR IN SENDING LEFT INDICATOR CAN MESSAGE");
  //   delay(5000);
  // }

  // Logic for Hazard
  if(HAZARD_BTN == HIGH)
  {
    sendMessage(6);
    Serial.println("CAN MESSAGE FOR HAZARD SEND SUCCESFULLY");
  }
  // else{
  //   Serial.println("ERROR IN SENDING HAZARD CAN MESSAGE");
  //   delay(5000);
  // }

  // Logic for IGNITION
  if(IGNITION_BTN == HIGH)
  {
    sendMessage(7);
    Serial.println("CAN MESSAGE FOR IGNITION SEND SUCCESFULLY");
  }
  // else{
  //   Serial.println("ERROR IN SENDING IGNITION CAN MESSAGE");
  //   delay(5000);
  // }

  // Logic for Latch
  if(LATCH_BTN == HIGH)
  {
    sendMessage(8);
    Serial.println("CAN MESSAGE FOR LATCH SEND SUCCESFULLY");
  }
  // else{
  //   Serial.println("ERROR IN SENDING LATCH CAN MESSAGE");
  //   delay(5000);
  // }

  // Logic for Head Lamp
  if(HEAD_LAMP_BTN == HIGH)
  {
    sendMessage(9);
    Serial.println("CAN MESSAGE FOR HEAD LAMP SEND SUCCESFULLY");
  }
  // else{
  //   Serial.println("ERROR IN SENDING HEAD LAMP CAN MESSAGE");
  //   delay(5000);
  // }
  if(BRAKE_BTN || RIGHT_INDICATOR_BTN || LEFT_INDICATOR_BTN || HAZARD_BTN || IGNITION_BTN || LATCH_BTN || HEAD_LAMP_BTN == LOW){
    Serial.println("PRESS THE BUTTON TO SEND CAN MESSAGE");
    delay(5000);
  }

}
 
void sendArray(byte *arr, int size, char messageId) {
  Serial.print("Sending array... ");
 
  CAN.beginPacket(messageId); // Set the ID
  for (int i = 0; i < size; i++) {
    CAN.write(arr[i]); // Write data to the buffer
  }
  CAN.endPacket();
 
  Serial.println("done");
}
  // for(int i = 0; i < noofMessages; i++){
  //   int canID = messages[i].msgid;
  //   byte* canData =  sendData[i];
  // //  byte sndStat = CAN0.sendMsgBuf(canID, 0, 8, canData);
  //   sendArray(canData, 8, canID); // Sending array1 with ID 0x123
  //   Serial.println("CAN ID: ");
  //   Serial.println(canID);
  //   Serial.println("CAN DATA: ");
  //   // Serial.println(canData);
  //   for (int j = 0; j < 8; j++) {
  //     Serial.print(canData[j], HEX); // Print data in hexadecimal format
  //     Serial.print(" ");
  //   }
  //   Serial.println();
 
 
  //   delay(100);
  // }