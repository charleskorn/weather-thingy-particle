#include "spark_wiring_ticks.h"

// Signature from spark_wiring_ticks.h

void delay(unsigned long ms) {
  HAL_Delay_Milliseconds(ms);
}

// Signatures from delay_hal.h

void HAL_Delay_Milliseconds(uint32_t millis) {
  // TODO
}

void HAL_Delay_Microseconds(uint32_t micros) {
  // TODO
}

// Signarures from timer_hal.h

system_tick_t HAL_Timer_Get_Micro_Seconds() {
  // TODO
  return 0;
}

system_tick_t HAL_Timer_Get_Milli_Seconds() {
  // TODO
  return 0;
}
