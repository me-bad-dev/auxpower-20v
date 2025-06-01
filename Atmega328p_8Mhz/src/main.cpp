/**
 * @file main.cpp
 * @brief WORKPRO / FastPower 20V Signal Emulator
 * 
 * This program emulates the digital handshake signal used by WORKPRO and FastPower 20V batteries.
 * It is intended to run on an ATmega328P microcontroller (e.g., Arduino Uno), configured to use 
 * its internal 8 MHz clock. The signal is output on Pin 9 using registers for fast digital write.
 * 
 * Pin Assignment:
 *   - Pin  9: Signal output pin (Battery C pin)
 *   - Pin 10: Status Led
 * 
 * Target Platform:
 *   - MCU: ATmega328P
 *   - Clock: 8 MHz (internal oscillator)
 *   - MCU Supply Voltage: 3.2V - 5.5V
 * 
 * Timing:
 *   - Pulse durations match captured handshake
 *   - Bitstream format and timing verified against original FASTPOWER 20V/4ah battery signal
 * 
 * Notes:
 *   - Ensure proper pull-down/pull-up configuration depending on output transistor or optocoupler
 *   - Suitable for battery replacement or tool testing with external power sources
 * 
 * Disclaimer:
 *   Use responsibly. Bypassing battery authentication may violate safety regulations or tool warranty.
 */

#include <Arduino.h>
#include <avr/pgmspace.h>

#define PWR_LED 10
#define C_PIN_MASK (1 << PB1) //Pin 9

struct Pulse {
  bool state;   
  int duration; 
};

const Pulse signalSequence[] PROGMEM = {
  {LOW, 925},
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
  {LOW, 300},
  {HIGH, 21035}
};

constexpr uint16_t pulseCount = sizeof(signalSequence) / sizeof(Pulse);

void fastDigitalWrite(uint8_t state) {
  if (state) PORTB |= C_PIN_MASK;   // Set HIGH
  else PORTB &= ~C_PIN_MASK;        // Set LOW
}

void setup() {
  DDRB |= C_PIN_MASK;    // Set Pin 9 as OUTPUT
  pinMode(PWR_LED, OUTPUT);
}

void loop() {
  digitalWrite(PWR_LED, !digitalRead(PWR_LED));
  
  for (uint16_t i = 0; i < pulseCount; i++) {
    Pulse pulse;
    memcpy_P(&pulse, &signalSequence[i], sizeof(Pulse));
    fastDigitalWrite(pulse.state);
    delayMicroseconds(pulse.duration);
  }
}
