/**
 * @file main.cpp
 * @brief WORKPRO / FastPower 20V Signal Emulator
 * 
 * This program emulates the digital handshake signal used by WORKPRO and FastPower 20V batteries.
 * It is intended to run on an ESP8266 microcontroller (e.g., D1 mini).
 * Dual channel signal output using registers GPIO5 & GPIO4 (D1 & D2 on the D1 mini)
 * 
 * Pin Assignment:
 *   - GPIO5: First output pin (Battery C pin)
 *   - GPIO4: Second output pin (Battery C pin)
 *   - LED_BUILTIN: Internal D1 LED (Status)
 * 
 * Target Platform:
 *   - MCU: ESP8266
 * 
 * Timing:
 *   - Pulse durations match captured handshake
 *   - Bitstream format and timing verified against original FASTPOWER 20V/4ah battery signal
 * 
 * Notes:
 *   - Ensure to use fast enough optocoupler. Avoid uing transitors for muli-channel output: battrery negative pins will have different potentials when connected in series.
 *   - Suitable for battery replacement or tool testing with external power sources
 * 
 * Disclaimer:
 *   Use responsibly. Bypassing battery authentication may violate safety regulations or tool warranty.
 */

#include <Arduino.h>
#include <pgmspace.h>

#define C_PIN1 5  //D1 - GPIO5
#define C_PIN2 4  //D2 - GPIO4

#define C_PIN1_MASK (1 << C_PIN1)
#define C_PIN2_MASK (1 << C_PIN2)

#define BOTH_PINS_MASK (C_PIN1_MASK | C_PIN2_MASK)

struct Pulse {
  bool state;   
  int duration; 
};

const Pulse signalSequence[] PROGMEM = {
  {HIGH, 21035}, {LOW, 925},
  {HIGH, 250}, {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, {LOW, 300}, 
  {HIGH, 250}, {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, {LOW, 300}, 
  {HIGH, 250}, {LOW, 300}, {HIGH, 250}, 
  {LOW, 570}, {HIGH, 250}, {LOW, 570}, {HIGH, 250}, {LOW, 570}, {HIGH, 250},
  {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, 
  {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, 
  {LOW, 300}, {HIGH, 250}, {LOW, 570}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, 
  {LOW, 570}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250},
  {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, 
  {LOW, 570}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250},
  {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, 
  {LOW, 300}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, {LOW, 570}, {HIGH, 250}, 
  {LOW, 300}, {HIGH, 250}, {LOW, 570}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, 
  {LOW, 570}, {HIGH, 250}, {LOW, 570}, {HIGH, 250}, {LOW, 570}, {HIGH, 250}, 
  {LOW, 570}, {HIGH, 250}, {LOW, 300}, {HIGH, 250}, {LOW, 570}, {HIGH, 250},
  {LOW, 300}
};

constexpr uint16_t pulseCount = sizeof(signalSequence) / sizeof(Pulse);

inline void fastDigitalWrite(bool state) {
  if (state) {
    GPOS = C_PIN1_MASK;  
  } else {
    GPOC = C_PIN1_MASK; 
  }
}

inline void fastDigitalWriteBoth(bool state) {
  if (state) {
    GPOS = BOTH_PINS_MASK;  // Set both pins high
  } else {
    GPOC = BOTH_PINS_MASK;  // Set both pins low
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(C_PIN1, OUTPUT); 
  pinMode(C_PIN2, OUTPUT); 

  fastDigitalWriteBoth(LOW);
}

void loop() 
{
  for (uint16_t i = 0; i < pulseCount; i++) {
    Pulse pulse;
    memcpy_P(&pulse, &signalSequence[i], sizeof(Pulse));
    fastDigitalWriteBoth(pulse.state);
    delayMicroseconds(pulse.duration);
  }
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
