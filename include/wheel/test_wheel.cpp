/* Interface L298N With NodeMCU
 * By TheCircuit
 */

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "../include/wheel/wheel.cpp"

int ENA = 4;
int IN1 = 0;
int IN2 = 2;

WHEEL wheel(4,0,2);

void setup() {
  wheel.initWheel();
}

// this function will run the motors in both directions at a fixed speed

void testOne() {
// turn on motor
digitalWrite(ENA, HIGH);  // set speed to 200 out of possible range 0~255
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);

delay(500); // now change motor directions

digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);

delay(500); // now turn off motors

digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
}

// this function will run the motors across the range of possible speeds
// note that maximum speed is determined by the motor itself and the operating voltage
// the PWM values sent by analogWrite() are fractions of the maximum speed possible by your hardware

void testTwo() {

// turn on motors
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);

// accelerate from zero to maximum speed
for (int i = 0; i < 256; i++)
  {
    analogWrite(ENA, i);
    delay(50);
   }

// decelerate from maximum speed to zero
for (int i = 255; i >= 0; --i)
    {
      analogWrite(ENA, i);
      delay(50);
     }

// now turn off motors
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
}

int cnt = 0;
void loop() {
  for (float i=-1; i<1; i+=0.2){
    wheel.setSpeed(i);
    delay(100);
  }
  
}
