# 📱💡 IoT Smart Light Control System

This project is a smart light control system using an **ESP8266** microcontroller. It allows you to control a lamp through:

- An **IR remote controller**
- A **mobile phone** (via WiFi)

It's ideal for smart home automation with both local (IR) and remote (mobile) control capabilities.

---

## 🔌 Hardware Requirements

- **ESP8266 (NodeMCU or similar)**
- **IR Receiver (e.g., TSOP382 or VS1838B)**
- **IR Remote Controller**
- **Relay Module** (to control the lamp)
- **Lamp** (or LED for testing)
- **Mobile Phone** (to access web UI or send commands via WiFi)

---

## 🚀 Features

- ✅ Control lamp via IR remote
- ✅ Control lamp from a mobile phone over WiFi
- ✅ ESP8266 acts as a web server
- ✅ Toggle lamp ON/OFF
- ✅ Low-cost and easy-to-build system

---

## 📁 Files

- `iot_System.ino` – Main firmware for ESP8266 with IR + mobile control
- `smart_light.ino` – Logic for smart control based on user inputs

---

## 🛠️ Setup Instructions

1. **Wiring**
   - Connect IR receiver to a digital pin (e.g., D2) on ESP8266
   - Connect the relay module to control the lamp (e.g., D1)
   - Power everything via USB or external power supply

2. **Software**
   - Open `.ino` files using Arduino IDE
   - Install required libraries:
     - `ESP8266WiFi`
     - `ESPAsyncWebServer`
     - `IRremoteESP8266` / `IRrecv`
   - Configure:
     - Your **WiFi SSID and password**
     - IR remote button codes (optional customization)

3. **Upload the code**
   - Choose correct board: **NodeMCU 1.0 (ESP8266)**
   - Select appropriate port and upload

4. **Usage**
   - Use your IR remote to control the lamp
   - Or connect your phone to the same WiFi network and access the ESP8266 web interface

---

## 📱 Mobile Control

Once uploaded, the ESP8266 will host a web interface accessible via IP (e.g., `192.168.1.xxx`). Use your browser on a mobile phone to:

- Turn lamp ON/OFF
- Check current status

---

## 🖥️ Serial Monitor

Use the Serial Monitor (9600 baud) for:

- IR debugging (check which button is pressed)
- WiFi status and IP address
- Command response logs

---

## 📜 License

MIT License – Free to use and modify.

---

## 👤 Author

**leo-gad**  
GitHub: [leo-gad](https://github.com/leo-gad)

