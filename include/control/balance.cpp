#ifndef BALANCE_INTERFACE
#define BALANCE_INTERFACE
#define GRAV_CONST (float) 10.25
//#define GRAV_CONST (float) 10.8

#include <cmath>
#include <Adafruit_Sensor.h>

class BALANCE{
public:
    //Controller Parameters

    float K = 0.07;//0.07
    float k_i = 20;//20
    float k_d = 25;//25
    float error = 0;
    float error_theshold = 0.7/(K*k_i);//0.7/(K*k_i) 
    float offset = -0.263;
    float offset_dot = 0.0;
    float mag_offset = 0.0;

    float arccos(float x){
        float ans = PI/2;
        ans -= x;
        ans -=pow(x,3)/6;
        ans -= 3* pow(x,5)/40;
        return ans;
    }

    float getTheta(sensors_vec_t accel){
        float x = accel.x;
        float y = accel.y;
        float z = accel.z;

        //Remove offset of IMU
        return PI/2 - arccos(z/GRAV_CONST);
    }

    float balanceController(sensors_vec_t accel, sensors_vec_t gyro){
        float theta = getTheta(accel);
        theta -= offset;
        float theta_dot = gyro.y;
        theta_dot -=offset_dot;
        error += theta;
        if (error>error_theshold) error = error_theshold;
        if (error<-error_theshold) error = -error_theshold;

        float mag = K*(theta + k_d*theta_dot + k_i*error);
        Serial.printf("Theta: %f\n", theta);
        Serial.printf("P:%f D:%f I:%f Total:%f \n ",K*theta, K*k_d*theta_dot, K*k_i*error, mag);
        if (mag > 1) mag = 1;
        if (mag <-1) mag = -1;
        return mag - mag_offset;
    }
}; 

#undef PI
#endif