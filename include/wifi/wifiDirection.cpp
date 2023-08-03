#ifndef WIFI
#define WIFI

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <functional>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* Put your SSID & Password */
const char* ssid = "MySon";  // Enter SSID here
const char* password = "12345678";  //Enter Password here

/* Put IP Address details */
IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

String getMainPage(int curState){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Human Controller</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: grey;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-active {display: block;width: 80px;background-color: green;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h3>Control</h3>\n";
  if (curState==1){
    ptr += "<a class=\"button-active\" href=\"/\">^</a>\n";
  }
  else{
    ptr += "<a class=\"button\" href=\"/up\">^</a>\n";
  }
  if (curState==2){
    ptr += "<a class=\"button-active\" href=\"/\">-></a>\n";
  }
  else{
    ptr += "<a class=\"button\" href=\"/right\">-></a>\n";
  }
  if (curState==3){
    ptr += "<a class=\"button-active\" href=\"/\">v</a>\n";
  }
  else{
    ptr += "<a class=\"button\" href=\"/down\">v</a>\n";
  }
  if (curState==4){
    ptr += "<a class=\"button-active\" href=\"/\"><-</a>\n";
  }
  else{
    ptr += "<a class=\"button\" href=\"/left\"><-</a>\n";
  }
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}

bool LED_STATUS = true;
int DIRECTION = 0;

void handlePage(){
  DIRECTION=0;
  server.send(200, "text/html", getMainPage(0)); 
}

void handlePageUp(){
  DIRECTION=1;
  server.send(200, "text/html", getMainPage(1)); 
}

void handlePageRight(){
  DIRECTION=2;
  server.send(200, "text/html", getMainPage(2)); 
}

void handlePageDown(){
  DIRECTION=3;
  server.send(200, "text/html", getMainPage(3)); 
}

void handlePageLeft(){
  DIRECTION=4;
  server.send(200, "text/html", getMainPage(4)); 
}

void setupWifi() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite (LED_BUILTIN, HIGH);

  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  server.on("/",handlePage);
  server.on("/up",handlePageUp);
  server.on("/right",handlePageRight);
  server.on("/down",handlePageDown);
  server.on("/left",handlePageLeft);

  server.begin();
  Serial.println("HTTP server started");
}
void loopWifi() {
  server.handleClient();
  Serial.printf("%i",DIRECTION);
}

#endif