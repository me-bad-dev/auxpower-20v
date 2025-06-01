
/*
#include <Arduino.h>

const int pwmPin = D1;  

//1400 - longest runtime
const int freqs[] = {750, 1000, 1075, 1400, 1562};
const int numFreqs = sizeof(freqs) / sizeof(freqs[0]);

// PWM range and duty cycle
const int pwmRange = 255;
const int dutyCycle = 143; // ~56% of 255
//135 - longest runtime

unsigned long lastSwitchTime = 0;
int currentFreqIndex = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);

  analogWriteRange(pwmRange);
  analogWriteFreq(freqs[currentFreqIndex]);
  analogWrite(pwmPin, dutyCycle);


}

void loop() 
{
  if (millis() - lastSwitchTime >= 20000) {
    currentFreqIndex = (currentFreqIndex + 1) % numFreqs;
    analogWriteFreq(freqs[currentFreqIndex]);
    analogWrite(pwmPin, dutyCycle);
    lastSwitchTime = millis();
  }
}
*/

#include <Arduino.h>
#include <pgmspace.h>

#define C_PIN1 5  // D1 - GPIO5
#define C_PIN2 4  // D2 - GPIO4

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

// Output to GPIO5 (D1)
inline void fastDigitalWrite(bool state) {
  if (state) {
    GPOS = C_PIN1_MASK;  
  } else {
    GPOC = C_PIN1_MASK; 
  }
}

// Output to both GPIO5 (D1) and GPIO4 (D2)
inline void fastDigitalWriteBoth(bool state) {
  if (state) {
    GPOS = BOTH_PINS_MASK;  // Set both high
  } else {
    GPOC = BOTH_PINS_MASK;  // Set both low
  }
}


void setup() {
  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(C_PIN1, OUTPUT); // D1
  pinMode(C_PIN2, OUTPUT); // D2

  fastDigitalWriteBoth(LOW);


}

void loop() 
{
  for (uint16_t i = 0; i < pulseCount; i++)
  {
    Pulse pulse;
    memcpy_P(&pulse, &signalSequence[i], sizeof(Pulse));
    fastDigitalWriteBoth(pulse.state);
    delayMicroseconds(pulse.duration);
  }
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}