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
XBeePoint2Point XBEE2(30, Serial, BYTE_ADDR_AIR);

void setup()
{
  //It initialize the serial port to receive data
  Serial.begin(57600);
  
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop()
{
  //Function to receive the data frame and store the data into "message" variable
  XBEE2.Receive(message, 4, BYTE_INIT_FRAME1);
  
  analogWrite(6, message[0]);
  analogWrite(9, message[1]);
  analogWrite(10, message[2]);
  analogWrite(11, message[3]);
  
}

