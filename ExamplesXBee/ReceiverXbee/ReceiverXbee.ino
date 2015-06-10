/************************************************************************
Example for sending one array of characters through XBee using the Library
XBeePoint2Point

This sketch can be used with any arduino

Pay attention to the pwm pins exclusively

Created by: Sergio Soler Valera
************************************************************************/
#include <XBeePoint2Point.h>

//Variable to store the data frame
unsigned char message[4];

//It creates the object with the constructor
//                 time  SerialPort  IdentifierXbee
XBeePoint2Point XBEE2(30, SERIALPORT0, BYTE_ADDR_AIR);

void setup()
{
  //It initialize the serial port to receive data
  XBEE2.Initialize(BAUDRATE3);
  
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
}

void loop()
{
  //Function to receive the data frame and store the data into "message" variable
  XBEE2.Receive(message, 4, BYTE_INIT_FRAME1);
  
  analogWrite(5, message[0]);
  analogWrite(6, message[1]);
  analogWrite(9, message[2]);
  analogWrite(10, message[3]);
  
}

