// CAN Send Example
//

#include <mcp_can.h>
#include <SPI.h>

const int USER_BTN = 15; 

MCP_CAN CAN0(5);     // Set CS to pin 10

byte sendData[][8] = {
    {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}, // Data for ID 1
    {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17}, // Data for ID 2
    {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27}, // Data for ID 3
    {0x03, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}, // Data for ID 4
    {0x14, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17}, // Data for ID 5
    {0x25, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27}, // Data for ID 6
    {0x06, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07}, // Data for ID 7
    {0x17, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17}, // Data for ID 8
  };


struct canMessage {
  char msgid;
  char msgname[30];
};

struct canMessage messages[] ={ 
  {0x124, "Engine"},
  {0x108, "Ignition"},
  {0x146, "Oil tank"},
  {0x17C, "coolant"},
  {0x126, "gear"},
  {0x227, "ABS"},
  {0x228, "WindSheild"},
  {0x2CC, "Doors"},
};

const int noofMessages = sizeof(messages)/sizeof(messages[0]);

void sendMessage()
{
  for(int i = 0; i < noofMessages; i++){
    int canID = messages[i].msgid;
    byte* canData =  sendData[i];
    byte sndStat = CAN0.sendMsgBuf(canID, 0, 8, canData);
    Serial.println("CAN ID: ");
    Serial.println(canID);
    Serial.println("CAN DATA: ");
    // Serial.println(canData);
    for (int j = 0; j < 8; j++) {
      Serial.print(canData[j], HEX); // Print data in hexadecimal format
      Serial.print(" ");
    }
    Serial.println();
    if(sndStat == CAN_OK){
      Serial.println("Message Sent Successfully!");
    } else {
      Serial.println("Error Sending Message...");
    }
    delay(500);
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(USER_BTN, INPUT);
  // Initialize MCP2515 running at 16MHz with a baudrate of 500kb/s and the masks and filters disabled.
  if(CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK) 
  Serial.println("MCP2515 Initialized Successfully!");
  else 
  Serial.println("Error Initializing MCP2515...");

  CAN0.setMode(MCP_NORMAL);   // Change to normal mode to allow messages to be transmitted
}



void loop()
{
  int buttonState = digitalRead(USER_BTN);
  if(buttonState == HIGH)
  {
    sendMessage();
    Serial.println("CAN MESSAGE SEND SUCCESFULLY");
  }
  else{
    Serial.println("ERROR IN SENDING CAN MESSAGE");
    delay(5000);
  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
