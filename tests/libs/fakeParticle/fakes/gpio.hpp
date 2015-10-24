#pragma once

#include "pinmap_hal.h"

// From wiring/inc/spark_wiring.h

void pinMode(uint16_t pin, PinMode mode);
PinMode getPinMode(uint16_t pin);
bool pinAvailable(uint16_t pin);
void digitalWrite(uint16_t pin, uint8_t value);
int32_t digitalRead(uint16_t pin);
void analogWrite(uint16_t pin, uint16_t value);
