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
  fakeParticle.setPinState(pin, value);
}

int32_t digitalRead(uint16_t pin) {
  return fakeParticle.getPinState(pin);
}

void analogWrite(uint16_t pin, PinState value) {
  throw NotImplementedException();
}
