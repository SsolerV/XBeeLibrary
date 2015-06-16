//
//  XBeePoint2Point.cpp
//  XBeePoint2Point
//
//  Created by Sergio Soler Valera on 1/6/15.
//  Copyright (c) 2015 Sergio Soler Valera. All rights reserved.
//

#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include "HardwareSerial.h"
#include <XBeePoint2Point.h>


//This is the constructor
//It requires the time between frames, the serial port and the identifier
//
//If his IDENTIFIER is Air, this wants to say the other Xbee must be Ground
//It assign the other to IDENTIFIER_AUX for sending the frame to the other XBee
//Otherwise, the IDENTIFIER will be GROUND  and the IDENTIFIER_AUX = AIR
XBeePoint2Point::XBeePoint2Point(int time = 30, Stream &serial = Serial, int identifier = BYTE_ADDR_AIR)
{
    //To assign the identifier to the global variable
    if (identifier == BYTE_ADDR_AIR)
    {
        IDENTIFIER = BYTE_ADDR_AIR; //Own address
        IDENTIFIER_AUX = BYTE_ADDR_GROUND;  //Destination address
    }
    else
    {
        IDENTIFIER = BYTE_ADDR_GROUND;  //Own address
        IDENTIFIER_AUX = BYTE_ADDR_AIR; //Destination address
    }
    
    //It assign the local value to the global variable
    //These global variables will not be modified anymore
    _serial = &serial;   //Serial port by defect Serial
    TIME = time;        //Default time is 30 milliseconds
    LAST_TIME = 0;      //It initialize this variable when the program starts
    
}


//This function is utilized to send data frames from one point to another point
//It must receive the array (data) with all data into, also the size of the array, the Serial Port and
//the identifier byte of data frame
void XBeePoint2Point::Send(unsigned char* data,int sizeFrame, int initFrame)
{
    int ack = 0; //Acknowledge
    int reSize = sizeFrame + 3;
    
    unsigned long timeNow = millis() - LAST_TIME;
    
    if (timeNow >= TIME) {
        
        LAST_TIME = millis();
        
        _serial->write(initFrame);
        _serial->write(IDENTIFIER_AUX); ack = IDENTIFIER_AUX;
        
        for (int i = 0; i < sizeFrame; i++) {
            _serial->write(data[i]); ack += data[i];
        }
        
        _serial->write(ack);
        
    }
    
    
}


//This function can be utilized to receive the data frame from the other XBee
//It receives the array to store the data and the size of the data frame
void XBeePoint2Point::Receive(unsigned char* data, int sizeFrame, int initFrame)
{
    int ack, ackReceived;
    int auxData[sizeFrame];
    int reSize = sizeFrame + 3;
    
    
    if(_serial->available() >= reSize)
    {
        char init = _serial->read();
        
        if(init == initFrame)
        {
            digitalWrite(13, HIGH);
            
            char addr = _serial->read();
            
            if(addr == IDENTIFIER)
            {
                ack = addr;
                
                for(int i = 0; i < sizeFrame; i++)
                {
                    auxData[i] = _serial->read();
                    ack += auxData[i];
                    
                }
                ack = (unsigned char)(ack);
                
                ackReceived = _serial->read();
                
                if (ackReceived == ack) {
                    for (int i = 0; i < sizeFrame; i++) {
                        data[i] = auxData[i];
                    }
                }
            }
            
        }
    }

}
