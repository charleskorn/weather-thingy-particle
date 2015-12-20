#include "action.hpp"
#include "fakeParticleDevice.hpp"

namespace FakeParticle {
  Action setPin(uint16_t pin, PinState state) {
    return [pin, state] (FakeParticleDevice& particle) -> void {
      particle.setPinDigitalState(pin, state);
    };
  }
}
