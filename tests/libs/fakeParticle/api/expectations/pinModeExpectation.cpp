#include "expectations.hpp"
#include "../fakeParticleDevice.hpp"
#include "../utilities.hpp"

using namespace std;

namespace FakeParticle {
  PinModeExpectation::PinModeExpectation(uint16_t pin, PinMode mode) :
    pin(pin),
    mode(mode) {
  }

  ConditionState PinModeExpectation::onTick(FakeParticleDevice& device) {
    if (device.getPinMode(pin) == mode) {
      return ConditionState::Passed;
    } else {
      return ConditionState::NotYetPassed;
    }
  }

  ostream& PinModeExpectation::describe(ostream& os) const {
    return os << "expect mode for pin " << pin << " to be " << pinModeToString(mode);
  }

  PinModeExpectation* pinModeIs(uint16_t pin, PinMode mode) {
    return new PinModeExpectation(pin, mode);
  }
}
