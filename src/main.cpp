// change MQTT topics to your own

#include <Arduino.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#include <ESP8266WiFi.h>
#include "Connectivity.h"
#include <PubSubClient.h>

// defines delay between measurements in milliseconds
// you can change this if you like to
#define DELAY 1000

// defines pin for indication LED and DS18B20 sensor
#define LED_PIN 12
const int oneWireBus = 14;

// creates object for oneWire bus
OneWire oneWire(oneWireBus);

// creates object for DS18B20 sensor
DallasTemperature temp(&oneWire);

// creates object for BMP280 sensor
Adafruit_BMP280 bmp;

void setup()
{
  // sets LED pin as output
  pinMode(LED_PIN, OUTPUT);

  // sets baudrate for serial communication
  Serial.begin(115200);

  // starts communication with DS18B20 sensor
  temp.begin();

  // starts communication with BMP280 sensor
  // note: 0x76 is default I2C address for BMP280 sensor, but it may differ in other cases
  if (!bmp.begin(0x76))
    while (1)
      ;

  // calls function to connect to WiFi - function is declared in Connectivity.h
  connectToWiFi();

  // calls function to connect to MQTT broker
  mqtt_client.setServer(mqtt_server, mqtt_port);

  // prints message to serial monitor and blinks LED to indicate that setup is done
  Serial.println("setup done");
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
}

void loop()
{
  // tells sensors to measure
  temp.requestTemperatures();
  bmp.takeForcedMeasurement();

  // declares and defines variables for temperature and pressure measured by sensors
  float DS18B20_temperature = temp.getTempCByIndex(0);
  float BMP280_temperature = bmp.readTemperature();
  float BMP280_pressure = bmp.readPressure() / 100.0F;

  // calls function to publish data to MQTT broker
  // first argument is topic, you would probably like to change it
  publishToMQTTBroker("meteo/bmptemperature", String(BMP280_temperature).c_str());
  publishToMQTTBroker("meteo/pressure", String(BMP280_pressure).c_str());
  publishToMQTTBroker("meteo/dallastemperature", String(DS18B20_temperature).c_str());

  // waits for a second before repeating the loop
  delay(DELAY);
}