#include "eeprom.hpp"

#include "fakeParticle.hpp"

using namespace FakeParticle;

EEPROMClass EEPROM;

uint8_t EEPROMClass::read(int idx) {
  return fakeParticle.getEEPROMValue(idx);
}

void EEPROMClass::write(int idx, uint8_t val) {
  fakeParticle.setEEPROMValue(idx, val);
}

void EEPROMClass::update(int idx, uint8_t val) {
  write(idx, val);
}
