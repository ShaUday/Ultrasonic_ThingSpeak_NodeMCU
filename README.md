Ultrasonic Sensor with NodeMCU and ThingSpeak
This project demonstrates real-time distance measurement using an HC-SR04 ultrasonic sensor connected to a NodeMCU ESP8266, with data sent to ThingSpeak for visualization. It showcases skills in IoT, embedded systems, and cloud integration.
Table of Contents

Overview
Hardware Requirements
Wiring
Software Setup
ThingSpeak Configuration
Code Explanation
Usage
Troubleshooting
Future Improvements

Overview
The HC-SR04 measures distance by sending ultrasonic pulses and calculating the time for the echo to return. The NodeMCU ESP8266 processes this data and sends it to ThingSpeak, a cloud platform for IoT data visualization, via Wi-Fi. The project includes Arduino code and setup instructions to replicate the system.
Hardware Requirements

NodeMCU ESP8266 (v1.0 or ESP-12E)
HC-SR04 Ultrasonic Sensor
Jumper wires
Breadboard (optional)
Micro-USB cable

Wiring
Connect the HC-SR04 to the NodeMCU as follows:



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


Note: If using 5V for VCC, add a voltage divider (e.g., 1kΩ and 2kΩ resistors) for the Echo pin to protect NodeMCU’s 3.3V GPIO.
Software Setup

Install Arduino IDE and configure for ESP8266 (assumed complete).
Install the ThingSpeak library:
Go to Sketch > Include Library > Manage Libraries.
Search for “ThingSpeak” by MathWorks and install.


Use the code in ultrasonic_thingSpeak.ino.

ThingSpeak Configuration

Sign up at thingspeak.com.
Create a new channel:
Name: Ultrasonic Sensor Data
Field 1: Distance (cm)
Save the channel.


Note the Channel ID and Write API Key from the API Keys tab.
Update the code with your Wi-Fi credentials, Channel ID, and Write API Key.

Code Explanation

Libraries: ESP8266WiFi.h for Wi-Fi connectivity, ThingSpeak.h for cloud communication.
HC-SR04 Logic: Sends a 10µs pulse via Trig, measures Echo duration, and calculates distance.
ThingSpeak: Sends distance data to Field 1 every 20 seconds (per free account limits).
Serial Monitor: Displays distance and upload status for debugging.

Usage

Wire the HC-SR04 to the NodeMCU as described.
Update ultrasonic_thingSpeak.ino with your Wi-Fi and ThingSpeak details.
Upload the code via Arduino IDE (NodeMCU 1.0, 115200 baud).
Open Serial Monitor to verify Wi-Fi and data sending.
View real-time data on ThingSpeak under your channel’s Private View.

Troubleshooting

No ThingSpeak Data: Check Channel ID, Write API Key, and Wi-Fi credentials. Ensure delay(20000) for free account limits.
Erratic Readings: Verify wiring, use a voltage divider for 5V VCC, ensure objects are within 2–400 cm.
Upload Issues: Confirm board/port settings, press NodeMCU’s “Boot” button if needed.

Future Improvements

Add multiple sensors (e.g., temperature) to other ThingSpeak fields.
Implement data filtering for smoother readings.
Add a local OLED display for real-time visualization.
Log data to a local server for redundancy.

License
MIT License - feel free to use and modify this code.

Built by [Your Name] to demonstrate IoT and embedded programming skills.
