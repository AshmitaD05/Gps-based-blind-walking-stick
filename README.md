# GPS-Based Blind Walking Stick

An IoT-powered assistive device designed to improve mobility, safety, and independence for visually impaired individuals.  
The smart walking stick integrates **ultrasonic sensors**, a **water sensor**, **camera-based object detection**, **GPS tracking**, and **emergency communication** via the **Twilio platform**.

---

## 📜 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Hardware Components](#hardware-components)
- [System Architecture](#system-architecture)
- [Working Principle](#working-principle)
- [Installation & Setup](#installation--setup)
- [How to Use](#how-to-use)
- [Results](#results)
- [Contributors](#contributors)

---

## 📖 Overview
Visually impaired individuals face significant challenges in navigation and safety due to limitations of traditional walking aids like white canes. This **GPS-based smart walking stick** provides:
- Real-time obstacle detection
- Water hazard detection
- Object recognition using AI (FOMO algorithm)
- Live GPS tracking
- Emergency location sharing to a guardian via SMS

---

## 🚀 Features
- **Obstacle Detection** → Ultrasonic sensors detect obstacles up to 100 cm and trigger a buzzer alert.
- **Water Detection** → Water level sensor detects wet/slippery surfaces and alerts with specific beep patterns.
- **Object Recognition** → ESP32-CAM uses FOMO AI algorithm to detect and classify objects.
- **GPS Tracking** → NEO-6M GPS module tracks user location in real time.
- **Emergency Communication** → Sends current location to a guardian through Twilio SMS with Google Maps link.
- **Low Power Consumption** → Uses ESP32-S3 for efficient performance.

---

## 🛠 Hardware Components
| No. | Component         | Specification |
|----|-------------------|--------------|
| 1  | ESP32-S3 WROOM-1  | AI-powered microcontroller with Wi-Fi & Bluetooth |
| 2  | Arduino UNO       | Camera module integration |
| 3  | GPS Module        | NEO-6M |
| 4  | Ultrasonic Sensor | HC-SR04, range 2–400 cm |
| 5  | Water Level Sensor| Range 0–3000 units |
| 6  | Push Button       | Emergency trigger |
| 7  | Buzzer            | Alert mechanism |
| 8  | Camera Module     | ESP32-CAM (OV2640) |
| 9  | Speaker           | 3W, 4Ω |
| 10 | Jumper Wires      | - |

---

## 🖥 System Architecture
**Main Modules:**
- **ESP32-S3** – Central control, GPS & Twilio integration, sensor data processing.
- **Arduino UNO** – ESP32-CAM integration for object detection.
- **Sensors** – Ultrasonic & water detection modules for hazard alerts.
- **Communication** – Twilio API for emergency SMS alerts.

---

## ⚙ Working Principle
1. **Obstacle Detection** – Ultrasonic sensor measures distance; buzzer alerts if obstacle < 100 cm.
2. **Water Detection** – Water sensor triggers different beep patterns based on water depth.
3. **Object Recognition** – ESP32-CAM + FOMO detects and identifies objects with ~85–90% accuracy.
4. **Emergency Alert** – Pressing the push button sends GPS coordinates to guardian’s phone.
5. **GPS + Twilio** – Extracts latitude/longitude, formats Google Maps link, sends via SMS.

---

## 📦 Installation & Setup
1. **Hardware Assembly** – Connect sensors, GPS, camera, buzzer, and buttons as per circuit diagram.
2. **Arduino IDE Setup**:
   - Install ESP32 board package.
   - Install required libraries: `ESP32`, `TinyGPS++`, `WiFi`, `HTTPClient`, `Twilio API`
3. **Twilio Setup**:
   - Create a Twilio account.
   - Get Account SID, Auth Token, and Phone Numbers.
4. **Upload Code** – Flash ESP32 and Arduino UNO with respective code files.

---

## 📌 How to Use
- Turn on the walking stick.
- System starts monitoring for obstacles, water, and objects continuously.
- Buzzer alerts trigger if an obstacle or water is detected.
- **In case of emergency**:
  - Press the push button.
  - Guardian receives an SMS with the live GPS location.

---

## 📊 Results
- **Obstacle Detection** → ±3 cm accuracy.
- **GPS Tracking** → ±3 m in open areas, ±10 m in urban areas.
- **Object Recognition** → ~85–90% accuracy using FOMO algorithm.
- **Water Detection** → Response time less than 1 second.

---

## 👨‍💻 Contributors
- **Ashmita D**
- **Samyuktha V**
- **Shri Namrutha S**  
Amrita School of Engineering, Coimbatore – Amrita Vishwa Vidyapeetham, Coimbatore.
