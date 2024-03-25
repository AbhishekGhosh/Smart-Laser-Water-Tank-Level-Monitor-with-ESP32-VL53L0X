#include <Wire.h>
#include <VL53L0X.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "YourWiFiSSID";
const char* password = "YourWiFiPassword";
const char* serverAddress = "http://yourserver.com/store_data.php";

VL53L0X sensor;
WiFiClient client;

void setup() {
  Serial.begin(115200);
  
  // Initialize the sensor
  Wire.begin();
  sensor.setTimeout(500);
  if (!sensor.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }
  sensor.startContinuous();
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  // Read water level from sensor
  uint16_t waterLevel = sensor.readRangeContinuousMillimeters();
  
  // Send data to server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverAddress);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String postData = "water_level=" + String(waterLevel);
    int httpResponseCode = http.POST(postData);
    if (httpResponseCode > 0) {
      Serial.println("Data sent successfully");
    } else {
      Serial.println("Error sending data");
    }
    http.end();
  } else {
    Serial.println("WiFi Disconnected. Unable to send data.");
  }
  
  // Wait for some time before next reading
  delay(5000); // Adjust delay as per requirement
}
