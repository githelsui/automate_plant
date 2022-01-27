#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ESP8266WebServer.h>
#include "twilio.hpp"
#include "keys_config.h"

// Use software serial for debugging?
#define USE_SOFTWARE_SERIAL 0

// Print debug messages over serial?
#define USE_SERIAL 1

const char* ssid = MAIN_SSID;
const char* password = WIFI_PASSWORD;
const char* account_sid = ACCOUNT_SID;
const char* auth_token = AUTH_TOKEN;

int sensor1 = A0;
int sensor2 = 10;
const int relay1 = 5;
const int relay2 = 6;
const int threshold = -5; //positive lvls > 0 = wet, negative lvls = dry
const int led = 16;
int lvl;
char res[64];

void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(sensor2, INPUT);
    pinMode(led, OUTPUT);
    pinMode(relay1, OUTPUT);
    pinMode(relay2, OUTPUT);
    Serial.println("Autoplant");
    digitalWrite(led, HIGH);
    delay(1000);
}

void flash(){
    Serial.println("Watering Plant");
    delay(500);  
    digitalWrite(led, LOW);
    delay(500); 
    digitalWrite(led, HIGH);
    delay(500); 
    digitalWrite(led, LOW);
    delay(500); 
    digitalWrite(led, HIGH);
    delay(500);  
    digitalWrite(led, LOW);
    delay(500); 
    digitalWrite(led, HIGH);
    delay(5000); 
} ‪

void checkMoisture(int plant, int pump, int sensor){
  
  lvl = analogRead(sensor);
  lvl = map(lvl, 550, 0, 0, 100);
  
  sprintf(res, "Moisture Level for Plant %3d: %3d\r\n", plant, lvl);
  Serial.print(res);

   if(lvl < threshold){
    digitalWrite(pump, HIGH);
    Serial.println("Pump on");
    delay(1000);  
    flash();  
    digitalWrite(pump, LOW);
    Serial.println("Pump off");
    delay(1000);
  } else {
    digitalWrite(led, HIGH);
    digitalWrite(pump, LOW);
    Serial.println("Pump off");
    delay(1000);
  }
  
}

void loop() {
  digitalWrite(led, HIGH);
  checkMoisture(1, relay1, sensor1);
  checkMoisture(2, relay2, sensor2);
 
//  delay(1000); //testing
  Serial.println("Will check moisture level again in 3 more days!");
  delay(259200000); //check every 3 days
}
