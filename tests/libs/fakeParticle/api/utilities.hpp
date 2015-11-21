#pragma once

#include <string>
#include "../fakes/gpio.hpp"

namespace FakeParticle {
  std::string pinStateToString(PinState state);
  std::string pinModeToString(PinMode mode);
}
