#include <Arduino.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <OneWire.h>
#include "env.h"

#define light 21
#define fan 19
#define dis_sensor 3
#define temp_sensor 2

OneWire oneWire(temp_sensor);	
DallasTemperature sensors(&oneWire);

void setup() {

  pinMode(light, OUTPUT);
  pinMode(fan, OUTPUT);
  pinMode(dis_sensor, INPUT);
  pinMode(temp_sensor,INPUT);

  Serial.begin(9600);
  WiFi.begin(WIFI_SSID,WIFI_PASS);

  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:

  if (WiFi.status() == WL_CONNECTED){
    
    //Post Request
    HTTPClient http;
  
    // Establish a connection to the server
    http.begin(endpoint);

    http.addHeader("Content-Type", "application/json");

    // Serialise JSON object into a string to be sent to the API
    StaticJsonDocument<150> doc;
    String httpRequestData;

    // Send the command to get temperatures
    sensors.requestTemperatures(); 

    //print the temperature in Celsius
    Serial.print("Temperature: ");
    Serial.println(sensors.getTempCByIndex(0));

    Serial.print("Distance: ");
    Serial.println(digitalRead(dis_sensor));


    doc["presence"] = digitalRead(dis_sensor);
    doc["temperature"] = sensors.getTempCByIndex(0);

    serializeJson(doc, httpRequestData);

    // Send HTTP POST request
    int httpResponseCode = http.PUT(httpRequestData);
    String http_response;

    // check reuslt of POST request. negative response code means server wasn't reached
     
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);

    http_response = http.getString();
    Serial.println(http_response);
      
    // Free resources
      http.end();
      delay(2000);

    //GET Request
    HTTPClient http;

    String http_response;

    http.begin(endpoint);

    int httpResponseCode = http.GET();

    if(httpResponseCode>0){
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);

      Serial.print("Response from server: ");
      http_response = http.getString();
      
    }
    else {
      Serial.print("Error Code: ");
      Serial.println(httpResponseCode);
    }

    http.end();

    // Stream& input;
    StaticJsonDocument<192> doc;

    DeserializationError error = deserializeJson(doc, http_response);

    if (error) {
      Serial.print("deserializeJson() failed:");
      Serial.println(error.c_str());
      return;
    }
    bool light_switch = doc["light_switch_1"]; // false
    bool fan_switch = doc["light_switch_2"]; // true

    Serial.println("");

    Serial.print("light_switch: ");
    Serial.println(light_switch);
    
    Serial.print("fan_switch: ");
    Serial.println(fan_switch);

    Serial.println("");
    //switch 1
    digitalWrite(light,light_switch);
    //switch 2
    digitalWrite(fan,fan_switch);
  }
  else {
    return;
  }
}