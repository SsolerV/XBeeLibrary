/************************************************************************
Example for sending one array of characters through XBee using the Library
XBeePoint2Point

Created by: Sergio Soler Valera
************************************************************************/
#include <XBeePoint2Point.h>

//It creates the object with the constructor
//                 time  SerialPort  IdentifierXbee
XBeePoint2Point XBEE1(30, Serial, BYTE_ADDR_GROUND);

void setup()
{
  //It initializes the serial port to send messages, baudrate = 57600
  //XBEE1.Initialize(BAUDRATE3);
  Serial.begin(57600);
  
}

void loop()
{
  //Array which contain the message to send to the other Arduino with XBee
  unsigned char message[4] = {0, 0, 0, 0};
  
  //The analog values are read and divide by 4 to convert range 0-255 (byte)
  message[0] = analogRead(A0) / 4;
  message[1] = analogRead(A1) / 4;
  message[2] = analogRead(A2) / 4;
  message[3] = analogRead(A3) / 4;
  
  
  //Method to send the message, just require the array, the size of it and identifier for the data frame
  XBEE1.Send(message, 4, BYTE_INIT_FRAME1);
  
}




