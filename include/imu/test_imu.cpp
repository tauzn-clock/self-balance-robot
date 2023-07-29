// Basic demo for accelerometer readings from Adafruit MPU6050

// ESP32 Guide: https://RandomNerdTutorials.com/esp32-mpu-6050-accelerometer-gyroscope-arduino/
// ESP8266 Guide: https://RandomNerdTutorials.com/esp8266-nodemcu-mpu-6050-accelerometer-gyroscope-arduino/
// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/

#include <Arduino.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include "../include/imu/imu.cpp"

IMU imu;

void setup(void) {
  imu.initIMU();
}

void loop() {
  imu.getEvents();
  
  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(imu.a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(imu.a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(imu.a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(imu.g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(imu.g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(imu.g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(imu.temp.temperature);
  Serial.println(" degC");

  Serial.println("");
  delay(500);
}