#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "../include/screen/screen.cpp"
#include "../include/imu/imu.cpp"
#include "../include/wheel/wheel.cpp"
#include "../include/control/balance.cpp"
#include "../include/wifi/wifiButton.cpp"

#define DEBUG false

//SCREEN screen;
IMU imu;
WHEEL wheel1(D7,D0,D1);
WHEEL wheel2(D8,D2,D3);
BALANCE balance;

void setup() 
{    

   Serial.begin(115200);
   Wire.begin(D6,D5);

   //screen.initScreen();
   //screen.writeText("Starting System",0,0);
   imu.initIMU();
   wheel1.initWheel();
   wheel2.initWheel();

   setupWifi();
}

void loop()
{ 
   //delay(1000);
   //screen.clearDisplay();
   imu.getEvents(); 
   float mag = balance.balanceController(imu.a.acceleration,imu.g.gyro,true);
   wheel1.setSpeed(mag);
   wheel2.setSpeed(mag);

   loopWifi();

   if (DEBUG){
      Serial.printf("Accel.x: %f\n",imu.a.acceleration.x);
      Serial.printf("Accel.y: %f\n",imu.a.acceleration.y);
      Serial.printf("Accel.z: %f\n",imu.a.acceleration.z);
      //Serial.printf("Gyro.x: %f\n",imu.g.gyro.x);
      Serial.printf("Gyro.y: %f\n",imu.g.gyro.y);
      //Serial.printf("Gyro.z: %f\n",imu.g.gyro.z);
      Serial.printf("Mag %f\n",mag);
      Serial.printf("Angle: %f\n",balance.getTheta(imu.a.acceleration));
      Serial.println("Still Alive");

      /*
      screen.writeText(imu.a.acceleration.x,0,0);
      screen.writeText(imu.a.acceleration.y,40,0);
      screen.writeText(imu.a.acceleration.z,80,0);

      screen.writeText(imu.g.gyro.x,0,20);
      screen.writeText(imu.g.gyro.y,40,20);
      screen.writeText(imu.g.gyro.z,80,20);

      screen.writeText(imu.temp.temperature,0,40);
      */
   }
}
