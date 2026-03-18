# 🏠 Eco Tech Domicile — Smart Sustainable Home

> An Arduino-based smart home system built with natural materials (palm branches + pottery clay), featuring smoke detection, motion-based security, and real-time temperature monitoring via Bluetooth.

**El Sadat STEM School · Team 25211 · Grade 11 · 2023–2024**  
**Team:** Ahmed Atef, Ahmed Abdallah, Kadry Mohamad, Mohamad Ayman, Marwan Yasser

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Hardware Components](#hardware-components)
- [Pin Configuration](#pin-configuration)
- [How It Works](#how-it-works)
- [Installation & Upload](#installation--upload)
- [Required Libraries](#required-libraries)
- [Project Structure](#project-structure)
- [Test Results](#test-results)
- [License](#license)

---

## Overview

Eco Tech Domicile is a prototype smart home that addresses Egypt's grand challenges around climate change and sustainable technology. The structure uses **palm branches and pottery clay** as natural, thermally insulating building materials — achieving an average of **4°C lower indoor temperature** compared to outside. A smart Arduino-based system handles safety, security, and environmental monitoring.

---

## Features

### 🔥 Smoke & Gas Leakage System
- MQ-2 sensor detects smoke/gas at two threshold levels (LOW: >350, HIGH: >500)
- On detection: opens a window via servo motor, activates fan for ventilation, triggers buzzer and LED alert
- Sends real-time Bluetooth notification to smartphone

### 🔒 Security System
- Arm/disarm using a 4×3 keypad with password codes (`#` + `111` to arm, `*` + `333` to disarm)
- IR sensor detects motion while system is armed
- Buzzer alarm + Bluetooth alert sent to smartphone on intrusion

### 🌡️ Temperature Monitoring
- Two LM35 sensors measure indoor and outdoor temperature simultaneously
- Readings sent over Bluetooth (HC-05) to a smartphone every second
- Validates the building's thermal insulation performance

### ⚡ Power Supply
- Powered by lithium-ion battery charged via solar cells (30S-20A charging module)

---

## Hardware Components

| Component         | Quantity | Purpose                            |
|-------------------|----------|------------------------------------|
| Arduino Uno       | 1        | Main microcontroller               |
| MQ-2 Sensor       | 1        | Smoke / gas detection              |
| IR Sensor         | 1        | Motion detection (security)        |
| LM35 Sensor       | 2        | Indoor & outdoor temperature       |
| HC-05 Bluetooth   | 1        | Wireless smartphone communication  |
| Servo Motor       | 2        | Window open/close + door lock      |
| DC Fan (12V)      | 1        | Ventilation on smoke detection     |
| 4×3 Keypad        | 1        | Security code input                |
| Buzzer            | 1        | Audible alerts                     |
| LED               | 1        | Visual alert indicator             |
| Polycarbonate     | -        | Windows and doors                  |
| Palm branches     | -        | Main structural material           |
| Pottery clay      | -        | Thermal insulation coating         |

---

## Pin Configuration

| Pin   | Component         |
|-------|-------------------|
| A0    | MQ-2 Sensor       |
| A1    | LM35 (Inside)     |
| A2    | LM35 (Outside)    |
| 2–4   | Keypad Columns    |
| 5–8   | Keypad Rows       |
| 9     | IR Sensor         |
| 10    | LED               |
| 11    | Buzzer            |
| 12    | Servo Motor       |
| 13    | Fan / Bluetooth TX|

> ⚠️ **Note:** Pin 13 is shared between the fan and Bluetooth TX in this version — review wiring carefully before uploading.

---

## How It Works

```
┌─────────────┐     ┌──────────────┐     ┌─────────────────────┐
│  Sensors    │────▶│  Arduino Uno │────▶│  Actuators          │
│  MQ-2       │     │              │     │  Servo (window)     │
│  IR Sensor  │     │  Processes   │     │  Fan (ventilation)  │
│  LM35 x2   │     │  Logic &     │     │  Buzzer (alert)     │
│  Keypad     │     │  Triggers    │     │  LED (indicator)    │
└─────────────┘     └──────┬───────┘     └─────────────────────┘
                           │
                           ▼
                    ┌──────────────┐
                    │  HC-05       │
                    │  Bluetooth   │──▶ Smartphone App
                    └──────────────┘
```

---

## Installation & Upload

1. **Install Arduino IDE** from [arduino.cc](https://www.arduino.cc/en/software)
2. **Install required libraries** (see below)
3. **Open** `src/Smart_home.ino` in the Arduino IDE
4. **Select board:** Tools → Board → Arduino Uno
5. **Select port:** Tools → Port → (your COM port)
6. Click **Upload** ✓

---

## Required Libraries

Install these via **Arduino IDE → Sketch → Include Library → Manage Libraries**:

| Library         | Install Name  | Purpose                        |
|-----------------|---------------|--------------------------------|
| Keypad          | `Keypad`      | 4×3 matrix keypad input        |
| SoftwareSerial  | Built-in      | Bluetooth serial communication |
| Servo           | Built-in      | Servo motor control            |

---

## Project Structure

```
eco-tech-domicile/
│
├── src/
│   └── Smart_home.ino       # Main Arduino sketch
│
├── schematics/
│   └── circuit_diagram.png  # Wiring diagram (add your Fritzing/image here)
│
├── docs/
│   ├── poster.pdf           # Project research poster
│   └── portfolio.pdf        # Full capstone portfolio report
│
├── libraries/               # Any custom libraries used
│
├── .gitignore
├── LICENSE
└── README.md
```

---

## Test Results

Temperature readings collected during testing (°C):

| Reading | Inside | Outside | Difference |
|---------|--------|---------|------------|
| 1       | 18.3   | 22.8    | **4.5°C**  |
| 2       | 18.0   | 22.4    | **4.4°C**  |
| 3       | 19.7   | 23.1    | **3.4°C**  |
| 4       | 18.1   | 22.7    | **4.6°C**  |

✅ Design requirement of ≥3°C temperature reduction was achieved in all readings.

---

## License

This project is licensed under the [MIT License](LICENSE).  
© 2024 Team 25211 — El Sadat STEM School
