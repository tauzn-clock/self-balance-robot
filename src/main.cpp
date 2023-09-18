#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
//#include "../include/screen/screen.cpp"
#include "../include/imu/imu.cpp"
#include "../include/wheel/wheel.cpp"
#include "../include/control/balance.cpp"
#include "../include/control/manual.cpp"
#include "../include/wifi/wifiDirection.cpp"

#define DEBUG false

IMU imu;
WHEEL wheel1(D7,D0,D1);
WHEEL wheel2(D8,D2,D3);
BALANCE balance;
MANUAL manual;

void setup() 
{    
   Serial.begin(115200);
   Wire.begin(D6,D5);
   imu.initIMU();
   wheel1.initWheel();
   wheel2.initWheel();

   //setupWifi(); TODO: Wifi Control
}

void loop()
{ 
   imu.getEvents(); 
   float balanceMag = balance.balanceController(imu.a.acceleration,imu.g.gyro);
   wheel1.setSpeed(balanceMag);
   wheel2.setSpeed(balanceMag);
   /*
   TODO: Wifi Control
   int direction = loopWifi();
   manual.handleInput(direction);
   wheel1.setSpeed(balanceMag + manual.leftWheel);
   wheel2.setSpeed(balanceMag + manual.rightWheel);
   */

   if (DEBUG){
      Serial.printf("Accel.x: %f\n",imu.a.acceleration.x);
      Serial.printf("Accel.y: %f\n",imu.a.acceleration.y);
      Serial.printf("Accel.z: %f\n",imu.a.acceleration.z);
      float accel_mag = imu.a.acceleration.x*imu.a.acceleration.x + imu.a.acceleration.y*imu.a.acceleration.y + imu.a.acceleration.z*imu.a.acceleration.z;
      accel_mag = pow(accel_mag,0.5);
      Serial.printf("Accel Mag:%f\n",accel_mag);
      Serial.printf("Gyro.y: %f\n",imu.g.gyro.y);
      Serial.printf("Angle: %f\n",balance.getTheta(imu.a.acceleration));
      Serial.println("Still Alive");
   }
}
