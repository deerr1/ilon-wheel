#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "Motor.h"
#include "index.h"
#include <Wire.h>
#include <GpioExpander.h>


// Передний левый мотор
#define FLSPEED A6
#define FLDIR A7
// Передний правый мотор
#define FRSPEED A5
#define FRDIR A4
//Задний левый мотор
#define BLSPEED 7 //!!! Изменить !!!
#define BLDIR 2 //!!! Изменить !!!
//Задний правый мотор
#define BRSPEED 1 //!!! Изменить !!!
#define BRDIR 0 //!!! Изменить !!!
//Максимальная скорость
#define MAX_SPEED 230.00

GpioExpander expander(42);

Motor motorFL(FLDIR, FLSPEED);
Motor motorFR(FRDIR, FRSPEED);
Motor motorBL(BLDIR, BLSPEED, SlotExpander);
Motor motorBR(BRDIR, BRSPEED, SlotExpander);
// Motor motorBR;

const char* ssid = "admin";
const char* password = "12345678";

ESP8266WebServer server(80);

void handleRoot() {
  String s = webpage;
  server.send(200, "text/html", s);
}

float map(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void motorSet() {
  float x1 = server.arg("x1").toFloat();
  float y1 = server.arg("y1").toFloat();
  float x2 = server.arg("x2").toFloat();
  float y2 = server.arg("y2").toFloat();

  int valLX = map(x1, -1.00, 1.00, -MAX_SPEED, MAX_SPEED);
  int valLY = map(y1, 1.00, -1.00, -MAX_SPEED, MAX_SPEED);
  int valRX = map(x2, -1.00, 1.00, -MAX_SPEED, MAX_SPEED);
  int valRY = map(y2, 1.00, -1.00, -MAX_SPEED, MAX_SPEED);

  // int valLX = x1;
  // int valLY = -y1;
  // int valRX = -x2;
  // int valRY = y2;

  // float dutyFR = valLY + valLX;
  // float dutyFL = valLY - valLX;
  // float dutyBR = valLY - valLX;
  // float dutyBL = valLY + valLX;

  // dutyFR += valRY - valRX;
  // dutyFL += valRY + valRX;
  // dutyBR += valRY - valRX;
  // dutyBL += valRY + valRX;

  Serial.print(valLX);
  Serial.print(" ");
  Serial.print(valLY);
  Serial.print(" ");
  Serial.print(valRX);
  Serial.print(" ");
  Serial.println(valRY);

  // motorFR.run(dutyFR);
  // motorFL.run(dutyFL);
  // motorBL.run(dutyBL);
  // motorBR.run(dutyBR);

  // motorFL.run(dutyFL);
  // motorFR.run(dutyFR);

  server.send(200);
  
}

void setup() {
  Serial.begin(9600);
  // while (!Serial) {
  // } 
  Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/motor_set", motorSet);
  Wire.begin();
  expander.begin();

  motorBL.expanderSet(expander);
  motorBR.expanderSet(expander);
  server.begin();

}

void loop() {
  server.handleClient();
}