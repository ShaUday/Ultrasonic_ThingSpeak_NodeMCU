#include <ESP8266WiFi.h>
#include <ThingSpeak.h>

// HC-SR04 Pins
#define TRIG_PIN D1 // GPIO 5
#define ECHO_PIN D2 // GPIO 4

// Wi-Fi Credentials
const char* ssid = "YOUR_WIFI_SSID"; // Replace with your Wi-Fi name
const char* password = "YOUR_WIFI_PASSWORD"; // Replace with your Wi-Fi password

// ThingSpeak Settings
unsigned long channelID = YOUR_CHANNEL_ID; // Replace with your Channel ID (e.g., 1234567)
const char* writeAPIKey = "YOUR_WRITE_API_KEY"; // Replace with your Write API Key
WiFiClient client;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set HC-SR04 pins
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
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
  
  // Print to Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Send data to ThingSpeak (Field 1)
  ThingSpeak.setField(1, distance);
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
