#include <Arduino.h>
#include <MillisTimer.h>
#include <avr/pgmspace.h>

#define PWR_LED 10

#define C_PIN_MASK (1 << PB1) //Pin 9

MillisTimer timerLed(750);

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
  if (state) PORTB |= C_PIN_MASK;   // Set HIGH (for Arduino Uno, adjust for other boards)
  else PORTB &= ~C_PIN_MASK;        // Set LOW
}

void setup() {
  DDRB |= C_PIN_MASK;    // Set Pin 9 as OUTPUT
  pinMode(PWR_LED, OUTPUT);
}

void loop() {

  if(timerLed.Expired(true)) {
    digitalWrite(PWR_LED, !digitalRead(PWR_LED));
  }

  for (uint16_t i = 0; i < pulseCount; i++) {
    Pulse pulse;
    memcpy_P(&pulse, &signalSequence[i], sizeof(Pulse));
    fastDigitalWrite(pulse.state);
    delayMicroseconds(pulse.duration);
  }
}