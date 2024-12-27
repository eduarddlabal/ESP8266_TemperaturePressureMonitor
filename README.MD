# ESP8266 Temperature and Pressure Monitor

This project is an IoT solution for monitoring temperature and pressure using an ESP8266 microcontroller. It collects data from sensors and publishes it to an MQTT broker.

## Features

- Connects to WiFi
- Collects temperature data from DS18B20 sensor
- Collects temperature and pressure data from BMP280 sensor
- Publishes sensor data to MQTT broker

## Hardware Requirements

- ESP8266 microcontroller
- DS18B20 temperature sensor
- BMP280 temperature and pressure sensor
- LED for indication
- 4k7 resistor
- 330R current-limiting resistor for LED

## Software Requirements

- PlatformIO IDE
- Arduino framework
- MQTT broker

## Installation
1. Clone the repository:
    ```sh
    git clone <repository_url>
    cd ESP8266_TemperaturePressureSensor
    ```

2. Open the project in PlatformIO IDE.

3. Update WiFi credentials and MQTT settings in `src/Connectivity.cpp`:
    ```cpp
    const char *ssid = "YOUR WIFI SSID";
    const char *password = "YOUR WIFI PASSWORD";
    const char *mqtt_server = "YOUR BROKER";
    const int mqtt_port = 1883;
    ```

4. Build and upload the project to the ESP8266.

## Usage
Build the circuit with help of schematic.pdf

1. Power up the ESP8266.
2. The device will connect to the specified WiFi network.
3. Sensor data will be published to the MQTT broker under the following topics:
    - `meteo/bmptemperature`
    - `meteo/pressure`
    - `meteo/dallastemperature`

## File Structure

- `.vscode/` - VSCode configuration files
- `include/` - Header files
- `lib/` - Project-specific libraries
- `src/` - Source files
- `test/` - Unit tests
- `platformio.ini` - PlatformIO project configuration file

##
- [PlatformIO](https://platformio.org/)
- [Arduino](https://www.arduino.cc/)
- [Adafruit](https://www.adafruit.com/)

this readme was written by Copilot AI

