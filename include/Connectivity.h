#ifndef __CONNECTIVITY_H__
#define __CONNECTIVITY_H__

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// wifi credentials
extern const char* ssid;
extern const char* password;

// mqtt settings
extern const char* mqtt_server;
extern const int mqtt_port;

extern WiFiClient espClient;
extern PubSubClient mqtt_client;

// declares functions for connecting to WiFi with preset credentials
void connectToWiFi();

// declares functions for connecting to MQTT broker with preset settings
void connectToMQTTBroker();

// declares functions for publishing messages to MQTT topic
void publishToMQTTBroker(const char* topic, const char* message);

#endif