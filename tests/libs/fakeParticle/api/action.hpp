#pragma once

#include <functional>

#include "spark_wiring_constants.h"

namespace FakeParticle {
  class FakeParticleDevice;

  using Action = std::function<void (FakeParticleDevice&)>;

  Action setPin(uint16_t pin, PinState value);
}
