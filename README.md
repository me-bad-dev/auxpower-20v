# WORKPRO / FastPower 20V C-Signal Emulator

⚡️ This project emulates the digital control signal used by **WORKPRO** and **FastPower 20V** lithium-ion batteries to enable operation of compatible lawn mowers and power tools without the original battery packs.

## 🔧 Overview

Many WORKPRO and FastPower tools expect a specific digital waveform on the **control pin (C pin)** of the battery terminal to verify battery presence. This project captures and replays that signal using a microcontroller — allowing the use of **DIY battery packs**, **bench power supplies**, or external power sources.

## ✅ Features

- Reproduces the handshake signal from WORKPRO / FastPower 20V packs
- Works on:
  - **ESP32 / ESP8266**
  - **Arduino UNO / Nano / ATmega328P**
- Supports:
  - Output via **transistor** or **optocoupler** (e.g., 2N2222, ILD615)
---
## 📦 Hardware Requirements

| Component         | Description                              |
|------------------|------------------------------------------|
| ESP32, ESP8266 or Arduino | Main controller                          |
| 2N2222 transistor or ILD615 optocoupler | Output signal isolation |
| Transistor / Optocoupler resistor | 1kΩ–4.5kΩ                  |
| Pull-down resistor | 1kΩ               |
---



## 🧰 Atmega 328p Wiring Example - Single Channel

**Using 2N2222 transistor (NPN):**
<div>
  <img src="https://github.com/me-bad-dev/fauxpower-20v/raw/main/Atmega328_scheme.png" width="80%">
</div>

## 🧰 ESP8266 Wiring Example - Dual Channel

**Using ILD615 2-channel optocoupler:**
<div>
  <img src="https://github.com/me-bad-dev/fauxpower-20v/raw/main/D1-Mini_scheme.png" width="80%">
</div>
