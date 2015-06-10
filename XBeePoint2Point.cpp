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

#include <XBeePoint2Point.h>

//This is the constructor
//It requires the time between frames, the serial port and the identifier
//
//If his IDENTIFIER is Air, this wants to say the other Xbee must be Ground
//It assign the other to IDENTIFIER_AUX for sending the frame to the other XBee
//Otherwise, the IDENTIFIER will be GROUND  and the IDENTIFIER_AUX = AIR
XBeePoint2Point::XBeePoint2Point(int time = 30, int serialPort = 0, int identifier = BYTE_ADDR_AIR)
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
    SERIALPORT = serialPort;    //Serial port by defect Serial
    TIME = time;        //Default time is 30 milliseconds
    LAST_TIME = 0;      //It initialize this variable when the program starts
    
}


//Setup the Serial Port and the baudrate. This function must be used into void setup()
/***********************************************
BAUDRATE0 ----------- 9600
BAUDRATE1 ----------- 19200
BAUDRATE2 ----------- 38400
BAUDRATE3 ----------- 57600
BAUDRATE4 ----------- 115200
************************************************/
void XBeePoint2Point::Initialize(int baudrate)
{
    switch (SERIALPORT) {
        case 0:
            
            if (baudrate == 0) {
                Serial.begin(9600);
            }
            else if (baudrate == 1){
                Serial.begin(19200);
            }
            else if (baudrate == 2){
                Serial.begin(38400);
            }
            else if (baudrate == 3){
                Serial.begin(57600);
            }
            else if (baudrate == 4){
                Serial.begin(115200);
            }
            else {
                Serial.begin(9600);
            }
            
            break;
            
    //Comment these three cases if you are not using the Arduino MEGA
       /*
        case 1:
            
            if (baudrate == 0) {
            Serial1.begin(9600);
            }
            else if (baudrate == 1){
            Serial.begin(19200);
            }
            else if (baudrate == 2){
            Serial1.begin(38400);
            }
            else if (baudrate == 3){
            Serial1.begin(57600);
            }
            else if (baudrate == 4){
            Serial1.begin(115200);
            }
            else {
            Serial1.begin(9600);
            }
        
            break;

        
        case 2:
            
            if (baudrate == 0) {
            Serial2.begin(9600);
            }
            else if (baudrate == 1){
            Serial2.begin(19200);
            }
            else if (baudrate == 2){
            Serial2.begin(38400);
            }
            else if (baudrate == 3){
            Serial2.begin(57600);
            }
            else if (baudrate == 4){
            Serial2.begin(115200);
            }
            else {
            Serial2.begin(9600);
            }

            break;
        
        case 3:
        
            if (baudrate == 0) {
            Serial.begin(9600);
            }
            else if (baudrate == 1){
            Serial.begin(19200);
            }
            else if (baudrate == 2){
            Serial.begin(38400);
            }
            else if (baudrate == 3){
            Serial.begin(57600);
            }
            else if (baudrate == 4){
            Serial.begin(115200);
            }
            else {
            Serial.begin(9600);
            }
        
            break;
        */
        
        default:
            
            
            if (baudrate == 0) {
                Serial.begin(9600);
            }
            else if (baudrate == 1){
                Serial.begin(19200);
            }
            else if (baudrate == 2){
                Serial.begin(38400);
            }
            else if (baudrate == 3){
                Serial.begin(57600);
            }
            else if (baudrate == 4){
                Serial.begin(115200);
            }
            else {
                Serial.begin(9600);
            }

            break;
    }
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
    
        //This part select the Serial Port and send the information by the selected Port
        switch (SERIALPORT) {
            case 0:
            
                Serial.write(initFrame);
                Serial.write(IDENTIFIER_AUX); ack = IDENTIFIER_AUX;
                
                for (int i = 0; i < sizeFrame; i++) {
                    Serial.write(data[i]); ack += data[i];
                }
                
                Serial.write(ack);
                
                break;
            
                
    //Comment these three cases if you are not using the Arduino MEGA
    /*

            case 1:
                Serial1.write(auxData, sizeFrame);
            
            case 2:
                Serial2.write(auxData, sizeFrame);
                break;
            
            case 3:
                Serial3.write(auxData, sizeFrame);
                break;
            
     */
                
            default:
                break;
        }
        
    }

    
}


//This function can be utilized to receive the data frame from the other XBee
//It receive the array to store the data and the size of the data frame
void XBeePoint2Point::Receive(unsigned char* data, int sizeFrame, int initFrame)
{
    int ack, ackReceived;
    int auxData[sizeFrame];
    int reSize = sizeFrame + 3;
    
    switch (SERIALPORT) {
        case 0:
            
            if(Serial.available() >= reSize)
            {
                char init = Serial.read();
                
                if(init == initFrame)
                {
                    digitalWrite(13, HIGH);
                    
                    char addr = Serial.read();
                    
                    if(addr == IDENTIFIER)
                    {
                        ack = addr;
                        
                        for(int i = 0; i < sizeFrame; i++)
                        {
                            auxData[i] = Serial.read();
                            ack += auxData[i];
                            
                        }
                        ack = (unsigned char)(ack);
                        
                        ackReceived = Serial.read();
                        
                        if (ackReceived == ack) {
                            for (int i = 0; i < sizeFrame; i++) {
                                data[i] = auxData[i];
                            }
                        }
                    }
                    
                }
            }
            break;
        
            //Comment these three cases if you are not using Arduino Mega
            /*
        case 1://Probando en mega
            
            if(Serial1.available() >= reSize)
            {
                char init = Serial1.read();

                if(init == initFrame)
                {
                    digitalWrite(13, HIGH);
                    
                    char addr = Serial1.read();
             
                    if(addr == IDENTIFIER)
                    {
                        ack = addr;
                        
                        for(int i = 0; i < sizeFrame; i++)
                        {
                            auxData[i] = Serial1.read();
                            ack += auxData[i];
                            
                        }
                        
                        ack = (unsigned char)(ack);
                        
                        ackReceived = Serial1.read();
                        
                        if (ackReceived == ack) {
                            for (int i = 0; i < sizeFrame; i++) {
                                data[i] = auxData[i];
                            }
                        }
                    }
                    
                }
            }

            break;
         
        case 2:
            
            if(Serial2.available() >= reSize)
            {
                char init = Serial2.read();
                
                if(init == initFrame)
                {
                    digitalWrite(13, HIGH);
                    
                    char addr = Serial2.read();
                    
                    if(addr == IDENTIFIER)
                    {
                        ack = addr;
                        
                        for(int i = 0; i < sizeFrame; i++)
                        {
                            auxData[i] = Serial2.read();
                            ack += auxData[i];
                            
                        }
                        ack = (unsigned char)(ack);
                        
                        ackReceived = Serial2.read();
                        
                        if (ackReceived == ack) {
                            for (int i = 0; i < sizeFrame; i++) {
                                data[i] = auxData[i];
                            }
                        }
                    }
                    
                }
            }

            break;
            
        case 3:
            
            if(Serial3.available() >= reSize)
            {
                char init = Serial3.read();
                
                if(init == initFrame)
                {
                    digitalWrite(13, HIGH);
                    
                    char addr = Serial3.read();
                    
                    if(addr == IDENTIFIER)
                    {
                        ack = addr;
                        
                        for(int i = 0; i < sizeFrame; i++)
                        {
                            auxData[i] = Serial3.read();
                            ack += auxData[i];
                            
                        }
                        ack = (unsigned char)(ack);
                        
                        ackReceived = Serial3.read();
                        
                        if (ackReceived == ack) {
                            for (int i = 0; i < sizeFrame; i++) {
                                data[i] = auxData[i];
                            }
                        }
                    }
                    
                }
            }

            break;*/
         
        default:
            
            if(Serial.available() >= reSize)
            {
                char init = Serial.read();
                
                if(init == initFrame)
                {
                    digitalWrite(13, HIGH);
                    
                    char addr = Serial.read();
                    
                    if(addr == IDENTIFIER)
                    {
                        ack = addr;
                        
                        for(int i = 0; i < sizeFrame; i++)
                        {
                            auxData[i] = Serial.read();
                            ack += auxData[i];
                            
                        }
                        ack = (unsigned char)(ack);
                        
                        ackReceived = Serial.read();
                        
                        if (ackReceived == ack) {
                            for (int i = 0; i < sizeFrame; i++) {
                                data[i] = auxData[i];
                            }
                        }
                    }
                    
                }
            }

            break;
    }
    
}