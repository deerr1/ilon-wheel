#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "Motor.h"
#include "index.h"
// пин управления скоростью мотора (с подержкой ШИМ)
// #define SPEED A6
// пин выбора направления движения мотора
// #define DIR A7

// Motor motor(A7, A6);

const char* ssid = "admin";
const char* password = "12345678";

ESP8266WebServer server(80);

void handleRoot() {
  String s = webpage;
  server.send(200, "text/html", s);
}

void motorSet() {
  int motorDir = server.arg("dir").toInt();
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
  // WiFi.mode(WIFI_STA);
  // WiFi.begin(ssid, password);
  Serial.println(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");
  // Serial.print("Connecting");
  // while (WiFi.status() != WL_CONNECTED) {
  //   delay(500);
  //   Serial.print(".");
  // }
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
  // покрутим в течении 3 секунд мотор в одну сторону
  server.handleClient();
}