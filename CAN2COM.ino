

#include <mcp_can.h>
#include <SPI.h>


long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[150];
char buffer [33];
int ok;


//INT 2
//SCK 
//SI
//SO               
MCP_CAN CAN0(10);                               // Set CS to pin 7
//GND
//VCC


void setup()
{
  Serial.begin(115200);
  
  // Initialize MCP2515 running at 16MHz with a baudrate of 125kb/s and the masks and filters disabled.
  // MAZDA CX-5 SETTINGS if(CAN0.begin(MCP_ANY, CAN_250KBPS, MCP_16MHZ) == CAN_OK) 
  if(CAN0.begin(MCP_ANY, CAN_250KBPS, MCP_16MHZ) == CAN_OK) 
     {
        Serial.println("\n\nMCP2515 Initialized Successfully!");
        ok=1;
     }
    else
      { 
        Serial.println("Error Initializing MCP2515...");
        ok=0;
      } 
 // CAN0.init_Mask(0,1,0x00000503); 
  
  //CAN0.init_Mask(0, 0,0xFFF);
//  CAN0.init_Filt(0, 1, 0x43E);
  //CAN0.init_Filt(1, 0, 0x202);
  CAN0.setMode(MCP_NORMAL);                     // Set operation mode to normal so the MCP2515 sends acks to received data.

  //pinMode(2, INPUT);                            // Setting pin 2 for /INT input
  
//  Serial.println("MCP2515 Library Receive Example...");
//  Serial.println("=======================OK=========================");
}

void loop()
{
 

 
 if(ok==1)                         // If pin 2 is low, read receive buffer
  {
   CAN0.readMsgBuf(&rxId, &len, rxBuf);      // Read data: len = data length, buf = data byte(s)
        if (true)
        {
            
            if((rxId & 0x80000000) == 0x80000000)     // Determine if ID is standard (11 bits) or extended (29 bits)
              sprintf(msgString, "E: %.8lX  DLC: %1d  Data:", (rxId & 0x1FFFFFFF), len);
            else
              sprintf(msgString, "S: %.3lX       DLC: %1d  Data:", rxId, len);
          
            Serial.print(msgString);
          
            if((rxId & 0x40000000) == 0x40000000){    // Determine if message is a remote request frame.
              sprintf(msgString, " REMOTE REQUEST FRAME");
              Serial.print(msgString);
            } else {
              for(byte i = 0; i<len; i++){
                sprintf(msgString, " %.2X", rxBuf[i]);
                Serial.print(msgString);
              }
              for(byte i = len; i<8; i++){
                sprintf(msgString, " 00");
                Serial.print(msgString);
              }

            }
            Serial.println();
        }


//     else
//    {
//              Serial.print("ID: ");
//              Serial.print(rxId, HEX);              
//              Serial.print(" Len: ");
//              Serial.print(len, DEC);              
//              Serial.print(" Data: ");
//              for(int i = 0; i<len; i++)           // Print each byte of the data
//              {
//                if(rxBuf[i] < 0x10)                // If data byte is less than 0x10, add a leading zero
//                {
//                  Serial.print("0");
//                }
//                Serial.print(rxBuf[i], HEX);
//                Serial.print(" ");                
//              }
//              Serial.println();
//    }     
        

  }
}

/*********************************************************************************************************
  END FILE
*********************************************************************************************************/


