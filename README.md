Smart Jar Cap with Ultrasonic Sensor and Custom Website
This IoT project creates a smart jar cap with an HC-SR04 ultrasonic sensor to measure the fill level of a jar, sending data to ThingSpeak and displaying it on a custom website. The NodeMCU ESP8266 uses WiFiManager for user-friendly Wi-Fi setup, and the website fetches data automatically, eliminating the need for users to input ThingSpeak API keys. This showcases skills in IoT, embedded systems, web development, and user-focused design.
Table of Contents

Overview
Hardware Requirements
Wiring
Software Setup
ThingSpeak Configuration
Wi-Fi Configuration
Website Setup
Code Explanation
Usage
Troubleshooting
Future Improvements

Overview
The HC-SR04, mounted in a jar cap, measures the distance to the jar’s contents, calculating the fill level (0% = empty, 100% = full). The NodeMCU sends data to ThingSpeak via Wi-Fi, configured through WiFiManager’s web portal. A custom website fetches and displays this data without requiring users to input ThingSpeak API keys, enhancing usability.
Hardware Requirements

NodeMCU ESP8266 (v1.0 or ESP-12E)
HC-SR04 Ultrasonic Sensor
Jar with cap (large enough for sensor)
Jumper wires
Breadboard or PCB (optional)
Micro-USB cable or 3.7V Li-ion battery with TP4056 module

Wiring
Connect the HC-SR04 to the NodeMCU:



HC-SR04 Pin
NodeMCU Pin
Notes



VCC
3V3
3.3V power (or 5V Vin with voltage divider for Echo)


Trig
D1 (GPIO 5)
Sends pulse


Echo
D2 (GPIO 4)
Receives pulse


GND
GND
Common ground


Note: If using 5V for VCC, add a voltage divider (1kΩ and 2kΩ resistors) for Echo.
Software Setup

Install Arduino IDE and configure for ESP8266 (assumed complete).
Install libraries:
ThingSpeak: Sketch > Include Library > Manage Libraries > Search "ThingSpeak".
WiFiManager: Search “WiFiManager” by tzapu.


Use SmartJarCap.ino for the NodeMCU.
For the website, use index.html (frontend-only) or server.js with public/index.html (backend).

ThingSpeak Configuration

Sign up at thingspeak.com.
Create a channel:
Name: Smart Jar Fill Level
Field 1: Distance (cm)
Field 2: Fill Level (%)
Save the channel.


Note the Channel ID, Write API Key, and Read API Key from the API Keys tab.
Update SmartJarCap.ino with Channel ID and Write API Key.
Use Read API Key in the website code (frontend or backend).

Wi-Fi Configuration

On first boot, connect to the “SmartJarCap” access point (password: “jar12345”).
Open the captive portal (192.168.4.1), select your Wi-Fi, and enter credentials.
The NodeMCU saves credentials and auto-connects on future boots.

Website Setup

Frontend-Only (Simple):
Use index.html to fetch data directly from ThingSpeak’s API.
Host on GitHub Pages or Netlify.

