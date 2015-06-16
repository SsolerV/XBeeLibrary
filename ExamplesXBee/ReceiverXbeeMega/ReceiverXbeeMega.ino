/************************************************************************
Example for sending one array of characters by XBee using the Library
XBeePoint2Point

Created by: Sergio Soler Valera
************************************************************************/
#include <XBeePoint2Point.h>

unsigned char MESSAGE[4];

//It creates the object with the constructor
//                 time  SerialPort  IdentifierXbee
XBeePoint2Point XBEE2(30, Serial1, BYTE_ADDR_AIR);

void setup()
{
  Serial.begin(115200);
  Serial1.begin(57600);
}

void loop()
{ 
  XBEE2.Receive(MESSAGE, 4, BYTE_INIT_FRAME1);
  
  Serial.print(MESSAGE[0]);
  Serial.print(" ");
  Serial.print(MESSAGE[1]);
  Serial.print(" ");
  Serial.print(MESSAGE[2]);
  Serial.print(" ");
  Serial.println(MESSAGE[3]);
  
}
