#include "action.hpp"
#include "fakeParticleDevice.hpp"

namespace FakeParticle {
  Action setPin(uint16_t pin, PinState value) {
    return [pin, value] (FakeParticleDevice& particle) -> void {
      particle.setPinState(pin, value);
    };
  }
}
