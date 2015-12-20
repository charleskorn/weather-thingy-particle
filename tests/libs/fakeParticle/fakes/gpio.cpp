#include "spark_wiring_ticks.h"

#include "gpio.hpp"
#include "fakeParticle.hpp"

using namespace FakeParticle;

void pinMode(uint16_t pin, PinMode mode) {
  fakeParticle.setPinMode(pin, mode);
}

PinMode getPinMode(uint16_t pin) {
  return fakeParticle.getPinMode(pin);
}

bool pinAvailable(uint16_t pin) {
  throw NotImplementedException();
}

void digitalWrite(uint16_t pin, PinState value) {
  fakeParticle.setPinDigitalState(pin, value);
}

int32_t digitalRead(uint16_t pin) {
  return fakeParticle.getPinDigitalState(pin);
}

void analogWrite(uint16_t pin, PinState value) {
  throw NotImplementedException();
}

int32_t analogRead(uint16_t pin) {
  return fakeParticle.getPinAnalogValue(pin);
}

bool waitForPin(pin_t pin, uint16_t value, unsigned long timeoutAt) {
  while (digitalRead(pin) != value) {
    if (micros() > timeoutAt) {
      return false;
    }
  }

  return true;
}

uint32_t pulseIn(pin_t pin, uint16_t value) {
  unsigned long timeoutAt = fakeParticle.getCurrentTimeInMicroseconds() + 3 * 1000 * 1000;

  // If the pin is already at the desired value, wait until it isn't, or time out after 3 seconds.
  if (!waitForPin(pin, !value, timeoutAt)) {
    return 0;
  }

  // Wait for the pin to be the desired value, or time out after 3 seconds.
  if (!waitForPin(pin, value, timeoutAt)) {
    return 0;
  }

  // Wait for the pin to not be the desired value, or time out after 3 seconds.
  unsigned long pulseStartedAt = fakeParticle.getCurrentTimeInMicroseconds();

  if (!waitForPin(pin, !value, timeoutAt)) {
    return 0;
  }

  return fakeParticle.getCurrentTimeInMicroseconds() - pulseStartedAt;
}
