#ifndef WIFI
#define WIFI

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <functional>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "./HttpPages.cpp"

class BASESTATION{
public:
    /* Put your SSID & Password */
    const char* ssid = "MySon";  // Enter SSID here
    const char* password = "12345678";  //Enter Password here

    /* Put IP Address details */
    IPAddress local_ip = IPAddress(192,168,1,1);
    IPAddress gateway = IPAddress(192,168,1,1);
    IPAddress subnet = IPAddress(255,255,255,0);

    ESP8266WebServer server = ESP8266WebServer(80);

    float controlledState[1] = {0};
};

BASESTATION tmp;

void handle_OnConnect() {
    tmp.controlledState[0] = 1;
    Serial.println("LED: OFF");
    tmp.server.send(200, "text/html", SendHTMLControl(HIGH)); 
}

void handle_led_on() {
    tmp.controlledState[0] = 1;
    Serial.println("LED: ON");
    tmp.server.send(200, "text/html", SendHTMLControl(HIGH)); 
}

void handle_led_off() {
    tmp.controlledState[0] = 0;
    Serial.println("LED: OFF");
    tmp.server.send(200, "text/html", SendHTMLControl(LOW)); 
}

void handle_NotFound(){
    tmp.server.send(404, "text/plain", "Not found");
}

void setupWifiControl(){
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite (LED_BUILTIN, HIGH);

    WiFi.softAP(tmp.ssid, tmp.password);
    WiFi.softAPConfig(tmp.local_ip, tmp.gateway, tmp.subnet);
    delay(100);
    
    tmp.server.on("/", handle_OnConnect);
    tmp.server.on("/ledon", handle_led_on);
    tmp.server.on("/ledoff", handle_led_off);
    tmp.server.onNotFound(handle_NotFound);
    
    tmp.server.begin();
    Serial.println("HTTP server started");
}

void loopWifiControl(){
    tmp.server.handleClient();
    if(tmp.controlledState[0]) digitalWrite(LED_BUILTIN, HIGH);
    else digitalWrite(LED_BUILTIN, LOW);
}
#endif