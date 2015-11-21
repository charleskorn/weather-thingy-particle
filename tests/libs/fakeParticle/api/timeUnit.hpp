#pragma once

#include <stdint.h>

namespace FakeParticle {
  enum class TimeUnit
  {
    Milliseconds,
    Microseconds
  };

  uint32_t toMicroseconds(uint32_t time, TimeUnit timeUnit);
}
