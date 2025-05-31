#include <ESP8266WiFi.h>
#include <WiFiManager.h> // For Wi-Fi configuration
#include <ThingSpeak.h>

// HC-SR04 Pins
#define TRIG_PIN D1 // GPIO 5
#define ECHO_PIN D2 // GPIO 4

// ThingSpeak Settings
unsigned long channelID = 2975866; // Replace with your Channel ID
const char* writeAPIKey = "X4PCBMTAM63PDM6B"; // Replace with your Write API Key
WiFiClient client;

// Jar dimensions (adjust as needed)
const float jarHeight = 20.0; // Jar height in cm (from cap to bottom)
const float sensorOffset = 2.0; // Distance from sensor to cap edge in cm

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set HC-SR04 pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Initialize WiFiManager
  WiFiManager wifiManager;
  // Uncomment to reset saved Wi-Fi settings for testing
  // wifiManager.resetSettings();
  
  // Start Wi-Fi configuration portal if not connected
  if (!wifiManager.autoConnect("SmartJarCap")) {
    Serial.println("Failed to connect to Wi-Fi");
    delay(3000);
    ESP.restart();
  }
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Initialize ThingSpeak
  ThingSpeak.begin(client);
}

void loop() {
  // Get distance from HC-SR04
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance = duration * 0.0343 / 2;
  
  // Calculate fill level (0% = empty, 100% = full)
  float maxDistance = jarHeight - sensorOffset; // Max measurable distance
  float fillLevel = (1 - (distance - sensorOffset) / maxDistance) * 100;
  if (fillLevel < 0) fillLevel = 0; // Clamp to 0% if negative
  if (fillLevel > 100) fillLevel = 100; // Clamp to 100% if over
  
  // Print to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Fill Level: ");
  Serial.print(fillLevel);
  Serial.println(" %");
  
  // Send data to ThingSpeak
  ThingSpeak.setField(1, distance);
  ThingSpeak.setField(2, fillLevel);
  int response = ThingSpeak.writeFields(channelID, writeAPIKey);
  
  // Check if data was sent successfully
  if (response == 200) {
    Serial.println("Data sent to ThingSpeak successfully");
  } else {
    Serial.println("Error sending data: HTTP " + String(response));
  }
  
  // Wait 20 seconds (ThingSpeak free account requires min 15s)
  delay(20000);
}
