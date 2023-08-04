#ifndef MANUAL_INTERFACE
#define MANUAL_INTERFACE

class MANUAL{
public:
    float linearMag = 0.3;
    float turnMag = 0.1;
    float leftWheel = 0;
    float rightWheel = 0;
    
    void handleInput(int dir){
        leftWheel=0;
        rightWheel=0;
        
        if (dir==1){
            leftWheel = -linearMag;
            rightWheel = -linearMag;
        }
        
        if (dir==2){
            leftWheel = linearMag;
            rightWheel = -linearMag;
        }

        if (dir==3){
            leftWheel = +linearMag;
            rightWheel = +linearMag;
        }

        if (dir==4){
            leftWheel = -linearMag;
            rightWheel = linearMag;
        }
    } 

};

#endif