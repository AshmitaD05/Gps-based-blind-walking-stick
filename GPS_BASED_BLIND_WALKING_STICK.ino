#include <WiFi.h>
#include <HTTPClient.h>
#include <base64.h>
#include <HardwareSerial.h>

// Wi-Fi Credentials
const char* ssid = "Lenovo P2";
const char* password = "samyuktha31";

// Twilio Credentials
const String account_sid = "USE TWILIO ACCOUNT SID";
const String auth_token = "USE YOUR TWILIO AUTH TOKEN";
const String twilio_number = "TWILIO NUMBER";
const String destination_number = "REPLACE WITH YOUR NUMBER";

// Button Pin
const int buttonPin = 15;
bool lastButtonState = HIGH;

// GPS Serial Setup
HardwareSerial GPS_Serial(1);
String gpsData = "";
float latitude = 0.0;
float longitude = 0.0;

// Ultrasonic & Water Sensor Pins
#define TRIG_PIN 4
#define ECHO_PIN 5
#define BUZZER_ULTRASONIC 6
#define WATER_SENSOR_PIN 1
#define BUZZER_WATER 7
#define DISTANCE_THRESHOLD 50

float duration_us, distance_cm;
int water_level = 0;

void setup() {
    Serial.begin(115200);
    GPS_Serial.begin(9600, SERIAL_8N1, 17, 18);
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_ULTRASONIC, OUTPUT);
    pinMode(BUZZER_WATER, OUTPUT);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected!");
}

void loop() {
    checkButtonPress();
    measureDistance();
    checkWaterLevel();
    delay(1000);
}

void checkButtonPress() {
    bool currentButtonState = digitalRead(buttonPin);
    if (lastButtonState == HIGH && currentButtonState == LOW) {
        Serial.println("Button Pressed! Reading GPS and sending SMS...");
        if (readGPSData()) {
            sendSMS(latitude, longitude);
        } else {
            Serial.println("Failed to read valid GPS data.");
        }
    }
    lastButtonState = currentButtonState;
}

bool readGPSData() {
    unsigned long startTime = millis();
    gpsData = "";
    while (millis() - startTime < 5000) {
        while (GPS_Serial.available()) {
            char c = GPS_Serial.read();
            gpsData += c;
        }
    }
    if (gpsData.indexOf("$GPGGA") != -1) {
        int latStart = gpsData.indexOf(",") + 1;
        for (int i = 0; i < 2; i++) latStart = gpsData.indexOf(",", latStart) + 1;
        int latEnd = gpsData.indexOf(",", latStart);
        String latStr = gpsData.substring(latStart, latEnd);
        char latDir = gpsData.charAt(latEnd + 1);
        int lonStart = gpsData.indexOf(",", latEnd + 2) + 1;
        int lonEnd = gpsData.indexOf(",", lonStart);
        String lonStr = gpsData.substring(lonStart, lonEnd);
        char lonDir = gpsData.charAt(lonEnd + 1);
        float latDD = latStr.substring(0, 2).toFloat() + (latStr.substring(2).toFloat() / 60);
        float lonDD = lonStr.substring(0, 3).toFloat() + (lonStr.substring(3).toFloat() / 60);
        if (latDir == 'S') latDD = -latDD;
        if (lonDir == 'W') lonDD = -lonDD;
        latitude = latDD;
        longitude = lonDD;
        Serial.print("Latitude: "); Serial.println(latitude, 6);
        Serial.print("Longitude: "); Serial.println(longitude, 6);
        return true;
    }
    return false;
}

void sendSMS(float latitude, float longitude) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        String url = "https://api.twilio.com/2010-04-01/Accounts/" + account_sid + "/Messages.json";
        String message_body = "Emergency! Location Coordinates:\n";
        message_body += "Latitude: " + String(latitude, 6) + "\n";
        message_body += "Longitude: " + String(longitude, 6) + "\n";
        message_body += "View on Map: https://www.google.com/maps?q=" + String(latitude, 6) + "," + String(longitude, 6);
        String postData = "To=" + destination_number + "&From=" + twilio_number + "&Body=" + message_body;
        String auth = base64::encode(account_sid + ":" + auth_token);
        http.begin(url);
        http.addHeader("Authorization", "Basic " + auth);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");
        int httpResponseCode = http.POST(postData);
        if (httpResponseCode > 0) {
            Serial.println("SMS Sent Successfully!");
        } else {
            Serial.print("Error sending SMS: ");
            Serial.println(httpResponseCode);
        }
        http.end();
    } else {
        Serial.println("WiFi not connected!");
    }
}

void measureDistance() {
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    duration_us = pulseIn(ECHO_PIN, HIGH);
    distance_cm = 0.017 * duration_us;
    Serial.print("Obstacle detected at distance: ");
    Serial.print(distance_cm);
    Serial.println(" cm");
    if (distance_cm < DISTANCE_THRESHOLD || distance_cm > 700) {
        digitalWrite(BUZZER_ULTRASONIC, HIGH);
        delay(500);
    } else {
        digitalWrite(BUZZER_ULTRASONIC, LOW);
    }
}

void checkWaterLevel() {
    water_level = analogRead(WATER_SENSOR_PIN);
    Serial.print("Water detected at Level: ");
    Serial.println(water_level);
    if (water_level > 1500) {
        for (int i = 0; i < 5; i++) {
            digitalWrite(BUZZER_WATER, HIGH);
            delay(200);
            digitalWrite(BUZZER_WATER, LOW);
            delay(200);
        }
    } else if (water_level >= 500 && water_level <= 1500) {
        for (int i = 0; i < 3; i++) {
            digitalWrite(BUZZER_WATER, HIGH);
            delay(500);
            digitalWrite(BUZZER_WATER, LOW);
            delay(500);
        }
    } else {
        digitalWrite(BUZZER_WATER, LOW);
    }
}