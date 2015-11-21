#pragma once

#include <stdint.h>
#include <vector>
#include <unordered_map>

#include "pinmap_hal.h"
#include "spark_wiring_constants.h"

#include "eventChain.hpp"
#include "timeUnit.hpp"
#include "expectations/expectations.hpp"

namespace FakeParticle {
  class FakeParticleDevice {
  public:
    FakeParticleDevice();

    void reset();
    void assertFinished();

    void setPinMode(uint16_t pin, PinMode mode);
    PinMode getPinMode(uint16_t pin);

    void setPinState(uint16_t pin, PinState state);
    PinState getPinState(uint16_t pin);

    void advanceClock(uint32_t microseconds);
    uint32_t getCurrentTimeInMicroseconds();

    EventChain& after(uint32_t time, TimeUnit timeUnit, Action action);
    EventChain& when(Condition* const condition, Action action);
    EventChain& expect(Expectation* const expectation);
    EventChain& immediately(Action action);

  private:
    std::vector<std::unique_ptr<EventChain>> eventChains;
    uint32_t currentTime;
    std::unordered_map<uint16_t, PinMode> pinModes;
    std::unordered_map<uint16_t, PinState> pinStates;
    bool alreadyProcessingStateChange;
    bool needToReprocessStateChange;

    void onStateChange();
  };

  extern FakeParticleDevice fakeParticle;
}