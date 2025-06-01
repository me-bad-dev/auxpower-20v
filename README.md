# WORKPRO / FastPower 20V Signal Emulator

⚡️ This project emulates the digital control signal used by **WORKPRO** and **FastPower 20V** lithium-ion batteries to enable operation of compatible lawn mowers and power tools without the original battery packs.

## 🔧 Overview

Many WORKPRO and FastPower tools expect a specific digital waveform on the **control pin (C pin)** of the battery terminal to verify battery presence. This project captures and replays that signal using a microcontroller — allowing the use of **DIY battery packs**, **bench power supplies**, or external power sources.

## ✅ Features

- Reproduces the authentic handshake signal from WORKPRO / FastPower 20V packs
- Works on:
  - **ESP32/ESP8266**
  - **Arduino UNO / Nano / ATmega328P**
- Supports:
  - Output via **transistor** or **optocoupler** (e.g., 2N2222, 6N137)
---
## 📦 Hardware Requirements

| Component         | Description                              |
|------------------|------------------------------------------|
| ESP32 or Arduino | Main controller                          |
| 2N2222 transistor or 6N137 optocoupler | Output signal isolation |
| Pull-up resistor | 1kΩ–10kΩ on output side                  |
| Pull-up resistor | 1kΩ–10kΩ on output side                  |
---



## 🧰 Atmega 328p Wiring Example

**Using 2N2222 transistor (NPN):**
![alt text]([https://github.com/me-bad-dev/fauxpower-20v/Atmega328_scheme.png](https://github.com/me-bad-dev/fauxpower-20v/blob/main/Atmega328_scheme.png) "Atmega 328p Wiring")
