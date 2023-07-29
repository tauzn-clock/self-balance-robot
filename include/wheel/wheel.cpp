#ifndef WHEEL_INTERFACE
#define WHEEL_INTERFACE

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>

class WHEEL{
public:
    int MAG, FOR, BAC;
    WHEEL(int _mag, int _for, int _bac): MAG(_mag), FOR(_for), BAC(_bac){}

    void initWheel(){
        pinMode(MAG, OUTPUT);
        pinMode(FOR, OUTPUT);
        pinMode(BAC, OUTPUT);
    }

    void setSpeed(float s){
        //Set threshold
        if (s>1) s=1;
        if (s<-1) s=-1;

        if (s>0){
            digitalWrite(FOR, LOW);
            digitalWrite(BAC, HIGH);
            analogWrite(MAG, (255*s));
        }
        else{
            digitalWrite(FOR, HIGH);
            digitalWrite(BAC, LOW);
            analogWrite(MAG, -(255*s));
        }
    }

    void stop(){
        digitalWrite(FOR, LOW);
        digitalWrite(BAC, LOW);
    }
};  

#endif