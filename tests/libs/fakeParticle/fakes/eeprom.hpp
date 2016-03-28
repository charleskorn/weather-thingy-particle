#pragma once

#include <stdint.h>

// From spark_wiring_eeprom.h

struct EEPROMClass {
  uint8_t read(int idx);
  void write(int idx, uint8_t val);
  void update(int idx, uint8_t val);
};

extern EEPROMClass EEPROM;