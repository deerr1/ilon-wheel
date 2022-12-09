#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "Motor.h"
#include "index.h"
// пин управления скоростью мотора (с подержкой ШИМ)
// #define SPEED A6
// пин выбора направления движения мотора
// #define DIR A7
#define MAX_SPEED 170.00
// Motor motor(A7, A6);

// MotorFL motor();
// MotorFR motor();
// MotorBL motor();
// MotorBR motor();

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
  float valLX = server.arg("x1").toFloat();
  float valLY = server.arg("y1").toFloat();
  float valRX = server.arg("x2").toFloat();
  float valRY = server.arg("y2").toFloat();


  // int valLX = map(x1, -1.00, 1.00, -MAX_SPEED, MAX_SPEED);
  // int valLY = map(y1, -1.00, 1.00, -MAX_SPEED, MAX_SPEED);
  // int valRX = map(x2, -1.00, 1.00, -MAX_SPEED, MAX_SPEED);
  // int valRY = map(y2, -1.00, 1.00, -MAX_SPEED, MAX_SPEED);

  float dutyFR = valLY + valLX;
  float dutyFL = valLY - valLX;
  float dutyBR = valLY - valLX;
  float dutyBL = valLY + valLX;

  dutyFR += valRY - valRX;
  dutyFL += valRY + valRX;
  dutyBR += valRY - valRX;
  dutyBL += valRY + valRX;


  Serial.print(x1);
  Serial.print(" ");
  Serial.print(y1);
  Serial.print(" ");
  Serial.print(x2);
  Serial.print(" ");
  Serial.println(y2);
  server.send(200);
  // motor.run(125 * motorDir);
  // if (motorDir == 0) {
  //   digitalWrite(DIR, HIGH);
  // } else {
  //   digitalWrite(DIR, LOW);
  // }
  // motorRun();
}

// void motorRun() {
//   digitalWrite(SPEED, HIGH);
//   delay(1000);
//   digitalWrite(SPEED, LOW);
// }

void setup() {
  Serial.begin(9600);
  Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", handleRoot);
  server.on("/motor_set", motorSet);
  server.begin();

}

void loop() {
  server.handleClient();
}