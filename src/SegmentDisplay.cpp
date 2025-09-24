/*
 Library written for use with Common-Anode 7-Segment Display. For more information on how to use this library,
 please refer to the github README.

 Written by: Derek Duncan
 Data: 2/4/2016
*/

#include "Arduino.h"
#include "SegmentDisplay.h"

SegmentDisplay::SegmentDisplay(int pin1, int pin2, int pin4, int pin5, int pin6, int pin7, int pin9, int pin10) {
    
    pins[0] = pin1;
    pins[1] = pin2;
    pins[2] = pin4;
    pins[3] = pin5;
    pins[4] = pin6;
    pins[5] = pin7;
    pins[6] = pin9;
    pins[7] = pin10;

    
    for(int i = 0; i < 8; i++) {
        pinMode(pins[i], OUTPUT);
        digitalWrite(pins[i], HIGH);
    }
}

void SegmentDisplay::displayHex(int number, boolean decimalPointFlag) {
    
    byte numbersToDisplay[] = {
        0b10001000,  //  0
        0b11101011,  //  1
        0b01001100,  //  2
        0b01001001,  //  3
        0b00101011,  //  4
        0b00011001,  //  5
        0b00011000,  //  6
        0b11001011,  //  7
        0b00001000,  //  8
        0b00001011,  //  9
        0b00001010,  //  A
        0b00111000,  //  B
        0b10011100,  //  C
        0b01101000,  //  D
        0b00011100,  //  E
        0b00011110,  //  F
        0b01011101  //  Error
        
    };
    
    
    boolean bitToWrite;
    
    for(int segment = 0; segment < 8; segment++) {
        if(number < 0 || number > 15) {
            bitToWrite = bitRead(numbersToDisplay[16], segment);
        }
        
        else if(segment == 3 && decimalPointFlag) {
            bitToWrite = 0;
        }
        
        else {
            bitToWrite = bitRead(numbersToDisplay[number], segment);
        }
        
        digitalWrite(pins[segment], bitToWrite);
        
    }
}

void SegmentDisplay::displayDecimalPoint() {
    for(int i = 0; i < 8; i++) {
        if(i == 3) {
            digitalWrite(pins[i], 0);
        }
        else {
            digitalWrite(pins[i], 1);
        }
    }
}

void SegmentDisplay::testDisplay() {
	for(int i = 0; i <= 15; i++) {
		displayHex(i, false);
		delay(500);
	}
}
