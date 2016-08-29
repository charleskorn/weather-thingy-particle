#include <sstream>

#include "expectations.hpp"
#include "../exceptions.hpp"
#include "../timeUnit.hpp"
#include "../fakeParticleDevice.hpp"
#include "../utilities.hpp"

using namespace std;

namespace FakeParticle {
  PinStateExpectation::PinStateExpectation(
    uint16_t pin,
    PinState desiredState,
    uint32_t minTime,
    uint32_t maxTime,
    TimeUnit timeUnit) :
      pin(pin),
      desiredState(desiredState),
      minTimeInMicroseconds(toMicroseconds(minTime, timeUnit)),
      maxTimeInMicroseconds(toMicroseconds(maxTime, timeUnit)),
      startedWaitingAt(0),
      haveStartedWaiting(false) {
  }

  ConditionState PinStateExpectation::onTick(FakeParticleDevice& device) {
    PinState currentPinState = device.getPinDigitalState(pin);
    uint32_t currentTime = device.getCurrentTimeInMicroseconds();

    if (!haveStartedWaiting) {
      if (currentPinState == desiredState) {
        startedWaitingAt = currentTime;
        haveStartedWaiting = true;
      } else {
        return ConditionState::NotYetPassed;
      }
    }

    if (currentPinState != desiredState) {
      if (currentTime < startedWaitingAt + minTimeInMicroseconds) {
        // If the pin has changed before min required time, fail.
        uint32_t pulseTime = currentTime - startedWaitingAt;

        ostringstream os;
        os << "Expected pin " << pin << " to be " << pinStateToString(desiredState);
        os << " for between " << minTimeInMicroseconds << " and " << maxTimeInMicroseconds << " microseconds,";
        os << " but changed to " << pinStateToString(currentPinState) << " after " << pulseTime << " microseconds.";

        throw AssertionFailedException(os.str());
      } else if (currentTime <= startedWaitingAt + maxTimeInMicroseconds) {
        // If the pin has changed between min and max time, pass.
        return ConditionState::Passed;
      }
    }

    // If we've gone longer than max time, fail.
    if (device.getCurrentTimeInMicroseconds() > startedWaitingAt + maxTimeInMicroseconds) {
      ostringstream os;
      os << "Expected pin " << pin << " to be " << pinStateToString(desiredState);
      os << " for between " << minTimeInMicroseconds << " and " << maxTimeInMicroseconds << " microseconds,";
      os << " but was " << pinStateToString(desiredState) << " for more than " << maxTimeInMicroseconds << " microseconds.";

      throw AssertionFailedException(os.str());
    }

    // Otherwise, wait.
    return ConditionState::NotYetPassed;
  }

  ostream& PinStateExpectation::describe(ostream& os) const {
    os << "expect pin " << pin << " to be " << pinStateToString(desiredState);
    os << " for between " << minTimeInMicroseconds << " and " << maxTimeInMicroseconds << " microseconds";

    return os;
  }

  PinStateExpectation* pinIsLow(uint16_t pin, uint32_t minTime, uint32_t maxTime, TimeUnit timeUnit) {
    return new PinStateExpectation(pin, LOW, minTime, maxTime, timeUnit);
  }

  PinStateExpectation* pinIsHigh(uint16_t pin, uint32_t minTime, uint32_t maxTime, TimeUnit timeUnit) {
    return new PinStateExpectation(pin, HIGH, minTime, maxTime, timeUnit);
  }
}
