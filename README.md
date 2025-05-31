# Smart Jar Cap with Ultrasonic Sensor and ThingSpeak

This project creates a smart jar cap with an HC-SR04 ultrasonic sensor to measure the fill level of a jar and send real-time data to ThingSpeak for visualization. It uses a NodeMCU ESP8266 and WiFiManager for user-friendly Wi-Fi configuration, eliminating hardcoded credentials. The project showcases IoT, embedded systems, and cloud integration skills.

## Table of Contents
- [Overview](#overview)
- [Hardware Requirements](#hardware-requirements)
- [Wiring](#wiring)
- [Software Setup](#software-setup)
- [ThingSpeak Configuration](#thingspeak-configuration)
- [Wi-Fi Configuration](#wi-fi-configuration)
- [Code Explanation](#code-explanation)
- [Usage](#usage)
- [Troubleshooting](#troubleshooting)
- [Future Improvements](#future-improvements)

## Overview
The HC-SR04 sensor, mounted in a jar cap, measures the distance to the jar’s contents, calculating the fill level (0% = empty, 100% = full). The NodeMCU ESP8266 sends this data to ThingSpeak via Wi-Fi, configured dynamically using WiFiManager’s web portal. The project includes Arduino code and setup instructions.

## Hardware Requirements
- NodeMCU ESP8266 (v1.0 or ESP-12E)
- HC-SR04 Ultrasonic Sensor
- Jar with cap (large enough for sensor)
- Jumper wires
- Breadboard or PCB (optional)
- Micro-USB cable or 3.7V Li-ion battery with TP4056 module

## Wiring
Connect the HC-SR04 to the NodeMCU:

| HC-SR04 Pin | NodeMCU Pin | Notes |
|-------------|-------------|-------|
| VCC         | 3V3         | 3.3V power (or 5V Vin with voltage divider for Echo) |
| Trig        | D1 (GPIO 5) | Sends pulse |
| Echo        | D2 (GPIO 4) | Receives pulse |
| GND         | GND         | Common ground |

**Note**: If using 5V for VCC, add a voltage divider (1kΩ and 2kΩ resistors) for Echo to protect NodeMCU’s 3.3V GPIO.

## Software Setup
1. Install Arduino IDE and configure for ESP8266 (assumed complete).
2. Install libraries:
   - **ThingSpeak**: `Sketch > Include Library > Manage Libraries > Search "ThingSpeak"`.
   - **WiFiManager**: Search “WiFiManager” by tzapu.
3. Use the code in `SmartJarCap.ino`.

## ThingSpeak Configuration
1. Sign up at [thingspeak.com](https://thingspeak.com).
2. Create a channel:
   - **Name**: Smart Jar Fill Level
   - **Field 1**: Distance (cm)
   - **Field 2**: Fill Level (%)
   - Save the channel.
3. Note the **Channel ID** and **Write API Key** from the **API Keys** tab.
4. Update the code with these details.

## Wi-Fi Configuration
1. The code uses WiFiManager to avoid hardcoding credentials.
2. On first boot, connect to the “SmartJarCap” access point.
3. Open the captive portal (192.168.4.1), select your Wi-Fi, and enter credentials.
4. The NodeMCU saves and auto-connects to Wi-Fi on subsequent boots.

## Code Explanation
- **Libraries**: `ESP8266WiFi.h`, `WiFiManager.h`, `ThingSpeak.h`.
- **HC-SR04**: Measures distance and calculates fill level based on jar height.
- **WiFiManager**: Creates a web portal for Wi-Fi setup.
- **ThingSpeak**: Sends distance (Field 1) and fill level (Field 2) every 20 seconds.
- **Serial Monitor**: Displays data and status for debugging.

## Usage
1. Mount the HC-SR04 in the jar cap, wire to NodeMCU.
2. Update `SmartJarCap.ino` with ThingSpeak Channel ID, Write API Key, and jar dimensions.
3. Upload code via Arduino IDE (NodeMCU 1.0, 115200 baud).
4. Configure Wi-Fi via the “SmartJarCap” portal.
5. Monitor data in Serial Monitor and ThingSpeak’s channel graphs.

## Troubleshooting
- **No ThingSpeak Data**: Verify Channel ID, Write API Key, and Wi-Fi. Ensure `delay(20000)`.
- **Wi-Fi Issues**: Connect to “SmartJarCap” AP and reconfigure credentials.
- **Erratic Readings**: Check wiring, use voltage divider for 5V VCC, ensure sensor alignment.
- **Upload Fails**: Confirm board/port settings, press “Boot” button if needed.

