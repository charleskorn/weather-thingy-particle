#pragma once

#include "spark_wiring_constants.h"
#include "../condition.hpp"

namespace FakeParticle {
    class Expectation : public Condition {
    public:

    protected:
      Expectation();
    };

    class PinStateExpectation : public Expectation {
    public:
      PinStateExpectation(uint16_t pin, PinState desiredState, uint32_t minTime, uint32_t maxTime, TimeUnit timeUnit);
      ConditionState onTick(FakeParticleDevice& device);
      std::ostream& describe(std::ostream& os) const;

    private:
      uint16_t pin;
      PinState desiredState;
      uint32_t minTimeInMicroseconds;
      uint32_t maxTimeInMicroseconds;

      uint32_t startedWaitingAt;
      bool haveStartedWaiting;
    };

    class PinModeExpectation : public Expectation {
    public:
      PinModeExpectation(uint16_t pin, PinMode mode);
      ConditionState onTick(FakeParticleDevice& device);
      std::ostream& describe(std::ostream& os) const;

    private:
      uint16_t pin;
      PinMode mode;
    };

    PinStateExpectation* pinIsLow(uint16_t pin, uint32_t minTime, uint32_t maxTime, TimeUnit timeUnit);
    PinStateExpectation* pinIsHigh(uint16_t pin, uint32_t minTime, uint32_t maxTime, TimeUnit timeUnit);
    PinModeExpectation* pinModeIs(uint16_t pin, PinMode mode);
}
