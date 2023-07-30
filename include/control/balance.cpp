#ifndef BALANCE_INTERFACE
#define BALANCE_INTERFACE
#define GRAV_CONST (float) 10.25
//#define GRAV_CONST (float) 10.8

#include <cmath>
#include <Adafruit_Sensor.h>

class BALANCE{
public:
    //Controller Parameters

    float K = 0.14;//Best K: 0.07
    float k_i = 8;//Best k_i: 20
    float k_d = 12;//Best k_d: 25
    float error = 0;
    float error_theshold = 0.7/(K*k_i); //Best Threshold: 0.7/(K*k_i)
    float offset = -0.263; //Best offset: -0.263
    float offset_dot = 0.0;
    float mag_offset = 0.0;

    float arcsin(float x){
        float ans = x;
        ans += pow(x,3)/6;
        ans += 3* pow(x,5)/40;
        return ans;
    }

    float getTheta(sensors_vec_t accel){
        //float x = accel.x;
        //float y = accel.y;
        float z = accel.z;

        //Remove offset of IMU
        return arcsin(z/GRAV_CONST);
    }

    float balanceController(sensors_vec_t accel, sensors_vec_t gyro, bool debug = false){
        float theta = getTheta(accel);
        theta -= offset;
        float theta_dot = gyro.y;
        theta_dot -= offset_dot;
        error += theta;

        //Threshold error
        if (error>error_theshold) error = error_theshold;
        if (error<-error_theshold) error = -error_theshold;

        float mag = K*(theta + k_d*theta_dot + k_i*error) - mag_offset;
        if (debug){
             Serial.printf("Theta: %f\n", theta);
            Serial.printf("P:%f D:%f I:%f Total:%f \n ",K*theta, K*k_d*theta_dot, K*k_i*error, mag);
        }
       

        return mag;
    }
}; 

#undef PI
#endif