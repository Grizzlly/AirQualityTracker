# Air Quality Tracker

## Introduction

The air quality tracker is a product built around the BME688 sensor. It aims to raise awareness about the air we breathe.

Using the companion app, you can create heatmaps for tracking the air quality around the places you walk, receive real-time warnings about harmful air and more!

## Overview

![Air Quality Tracker](https://ocw.cs.pub.ro/courses/_media/pm/prj2025/eradu/andrei.stan0305/airqualitytracker.png)

The ESP32 communicates with the sensor via I2C. It collects data about gas, temperature, humidity, and pressure. In turn, the ESP32 communicates with the companion app via BLE (Bluetooth Low Energy), which collects all data from the sensor.

### Components

- **[ESP32](https://www.optimusdigital.ro/ro/placi-cu-wifi/3053-placa-de-dezvoltare-esp32-cu-wifi-si-bluetooth.html?)**
- **[BME688 sensor](https://www.digikey.ro/ro/products/detail/bosch-sensortec/BME688/13681261)**
- **[Power Supply](https://www.optimusdigital.ro/ro/electronica-de-putere-stabilizatoare-liniare/61-sursa-de-alimentare-pentru-breadboard.html)**
- **Companion App**

## Hardware Design

### Schematic

![Schematic](https://ocw.cs.pub.ro/courses/_media/pm/prj2025/eradu/andrei.stan0305/schematic.png)

### Bill of Materials

- **[ESP32](https://www.optimusdigital.ro/ro/placi-cu-wifi/3053-placa-de-dezvoltare-esp32-cu-wifi-si-bluetooth.html?)**
- **[BME688 sensor](https://www.digikey.ro/ro/products/detail/bosch-sensortec/BME688/13681261)**
- **[4.7kOhm Resistor](https://www.optimusdigital.ro/ro/componente-electronice-rezistoare/849-rezistor-025w-47k.html)**
- **[47 nF Capacitor](https://www.optimusdigital.ro/ro/componente-electronice-condensatoare/7817-condensator-ceramic-47-nf-50-v.html)**

## Software Design

The ESP32 is programmed in PlatformIO using the Arduino Framework. The Adafruit Sensor Library communicates efficiently with the sensor.

The companion app is built using .NET technologies. It uses the Shiny.NET third-party library, which makes it easy to use BLE functionalities.  
The app also integrates the Google Maps API to display heatmaps.

## Results

Unfortunately, this project has been doomed from the start. The hardware part should have been the simplest one, yet it has given me the most headaches.

I used 2 sensors, but I was unable to communicate with them in any way. The mobile application functions correctly, as it connects to the ESP32 and receives dummy data.

## Conclusions

This was an interesting project nonetheless, and I also managed to see real value while working with the Google Maps API. In Romania, there is no Air Quality coverage layer on the map.
