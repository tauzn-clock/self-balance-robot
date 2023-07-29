#ifndef INFRARED_INTERFACE
#define INFRARED_INTERFACE

#include <Arduino.h>

class InfraredObj{

public:
    int inputPin;
    InfraredObj(int _inputPin): inputPin(_inputPin){}
    void setup(){
        pinMode(inputPin, INPUT); // declare Infrared sensor as input
    }

    int loop(){
        return digitalRead(inputPin);
    }

};

#endif