/*
  Keyboard test

  For the Arduino Leonardo, Micro or Due

  Reads a byte from the serial port, sends a keystroke back.
  The sent keystroke is one higher than what's received, e.g. if you send a,
  you get b, send A you get B, and so forth.

  The circuit:
  - none

  created 21 Oct 2011
  modified 27 Mar 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/KeyboardSerial
*/

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "ESP8266WiFi.h"
#include "./wifi/KEEPSECRET.cpp"
#include "./ThingSpeak/ThingSpeak.h"

WiFiClient  client;

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode (LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, LOW);

  // Connect to WiFi
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);

  // while wifi not connected yet, print '.'
  // then after it connected, get out of the loop
  /*
  while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print(".");
  }
  */
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");

  // Print the IP address
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

int cnt = 0;

void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);                 
  
  //print a new line, then print WiFi connected and the IP address
  Serial.println("");
  Serial.println("WiFi connected");
  // Print the IP address
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.macAddress());

  cnt++;
  cnt%=10;
  if (cnt==0) ThingSpeak.writeField(CHANNEL_NUMBER, 1, 100, WRITE_API);
}

