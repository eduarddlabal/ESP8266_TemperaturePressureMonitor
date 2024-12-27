// change wifi credentials and mqtt settings to match your setup
// some debug serial prints are commented out, you can uncomment them if you like to 

#include "Connectivity.h"

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// defines pin for indication LED
#define LED_PIN 12

WiFiClient espClient;
PubSubClient mqtt_client(espClient);

// wifi credentials
const char *ssid = "YOUR WIFI SSID";
const char *password = "YOUR WIFI PASSWORD";

// mqtt settings
const char *mqtt_server = "YOUR BROKER";
const int mqtt_port = 1883;

// defines function to connect to WiFi
void connectToWiFi()
{
    WiFi.begin(ssid, password);
    Serial.print("connecting");
    // waits until wifi is connected
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWIFI: successfully connected");
}

// defines function to connect to MQTT broker
void connectToMQTTBroker()
{
    while (!mqtt_client.connected())
    {
        String client_id = "esp8266-" + String(WiFi.macAddress());
        // Serial.printf("connecting to MQTT Broker as %s.....\n", client_id.c_str());
        if (mqtt_client.connect(client_id.c_str()))
        {
            // Serial.println("MQTT: succesfully connected to broker");
        }
        else
        {
            Serial.print("Failed to connect to MQTT broker, rc=");
            Serial.print(mqtt_client.state());
            Serial.println(" try again in 5 seconds");
            delay(5000);
        }
    }
}

// defines function to publish messages to MQTT topic
void publishToMQTTBroker(const char *topic, const char *message)
{
    // checks if wifi is connected
    if (WiFi.status() != WL_CONNECTED)
        connectToWiFi();

    // checks if mqtt client is connected
    if (!mqtt_client.connected())
        connectToMQTTBroker();

    // publishes message to mqtt topic
    mqtt_client.publish(topic, message);

    // sends debug message to serial monitor
    Serial.printf("MQTT: published to %s: %s\n", topic, message);

    // blinks LED to indicate that message was published
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
}