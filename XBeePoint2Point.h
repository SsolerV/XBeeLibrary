//
//  XBeePoint2Point.h
//  XBeePoint2Point
//
//  Created by Sergio Soler Valera on 1/6/15.
//  Copyright (c) 2015 Sergio Soler Valera. All rights reserved.
//

#ifndef XBeePoint2Point_h
#define XBeePoint2Point_h
#define LIBRARY_VERSION 0.0.1

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

//#include <inttypes.h>

class XBeePoint2Point
{
    
    
public:
    
    //Constants used in some of the functions below
#define SERIALPORT0 0
#define SERIALPORT1 1
#define SERIALPORT2 2
#define SERIALPORT3 3
    
    //Using these constants we will not have problem with the setup and the
    //function which use them
    
#define BAUDRATE0 0     //9600
#define BAUDRATE1 1     //19200
#define BAUDRATE2 2     //38400
#define BAUDRATE3 3     //57600
#define BAUDRATE4 4     //115200
    
#define BYTE_ADDR_AIR 0x11          //Mode, one of them must be the AIR and the other, the ground
#define BYTE_ADDR_GROUND 0x13
    
#define BYTE_INIT_FRAME1 0x4E       //Data frame indentifier
#define BYTE_INIT_FRAME2 0x5E       //Must be the same in functions Send() and Receive()
#define BYTE_INIT_FRAME2 0x6E
#define BYTE_INIT_FRAME2 0x7E
    
    
    
    //commonly used functions **************************************************************************
    //XBeePoint2Point(int, int, int);       // Default constructor
    
    XBeePoint2Point(int, Stream &serial, int);
    
    void Send(unsigned char*, int, int);    //Send the information to the other XBee
    
    void Receive(unsigned char*, int, int);     //Receive the information from the other XBee
    
    
    
private:
    
    int IDENTIFIER;        //Global value of the identifier
    int IDENTIFIER_AUX;     //Global value of the identifier of the other XBee
    int SERIALPORT;         //Global value of the serial port
    int* DATA;
    unsigned int TIME;      //Time between messages
    unsigned long LAST_TIME;     //Store the time in a global value to control the time between messages
    Stream* _serial;
    
   

};
#endif
