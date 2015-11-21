#include "spark_wiring_ticks.h"

#include "fakeParticle.hpp"

using namespace FakeParticle;

// Signature from spark_wiring_ticks.h

void delay(unsigned long ms) {
  HAL_Delay_Milliseconds(ms);
}

// Signatures from delay_hal.h

void HAL_Delay_Milliseconds(uint32_t millis) {
  fakeParticle.advanceClock(millis * 1000);
}

void HAL_Delay_Microseconds(uint32_t micros) {
  fakeParticle.advanceClock(micros);
}

// Signarures from timer_hal.h

system_tick_t HAL_Timer_Get_Micro_Seconds() {
  fakeParticle.advanceClock(1);
  return fakeParticle.getCurrentTimeInMicroseconds();
}

system_tick_t HAL_Timer_Get_Milli_Seconds() {
  fakeParticle.advanceClock(1);
  return fakeParticle.getCurrentTimeInMicroseconds() / 1000;
}
