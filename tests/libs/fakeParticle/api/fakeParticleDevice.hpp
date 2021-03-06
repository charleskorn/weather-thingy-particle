#pragma once

#include <stdint.h>
#include <vector>
#include <unordered_map>
#include <memory>

#include "pinmap_hal.h"
#include "spark_wiring_constants.h"

#include "eventChain.hpp"
#include "timeUnit.hpp"
#include "expectations/expectations.hpp"
#include "particleEvent.hpp"

namespace FakeParticle {
  class FakeParticleDevice {
  public:
    FakeParticleDevice();

    void reset();
    void assertFinished();

    void setPinMode(uint16_t pin, PinMode mode);
    PinMode getPinMode(uint16_t pin);

    void setPinDigitalState(uint16_t pin, PinState state);
    PinState getPinDigitalState(uint16_t pin);

    void setPinAnalogValue(uint16_t pin, int32_t value);
    int32_t getPinAnalogValue(uint16_t pin);

    void setEEPROMValue(int slot, uint8_t value);
    uint8_t getEEPROMValue(int slot);

    void advanceClock(uint32_t microseconds);
    uint32_t getCurrentTimeInMicroseconds();

    EventChain& after(uint32_t time, TimeUnit timeUnit, Action action);
    EventChain& when(Condition* const condition, Action action);
    EventChain& expect(Expectation* const expectation);
    EventChain& immediately(Action action);

    void publishEvent(const ParticleEvent event);
    std::vector<ParticleEvent>& getPublishedEvents();

  private:
    std::vector<std::unique_ptr<EventChain>> eventChains;
    uint32_t currentTime;
    std::unordered_map<uint16_t, PinMode> pinModes;
    std::unordered_map<uint16_t, PinState> pinDigitalStates;
    std::unordered_map<uint16_t, int32_t> pinAnalogValues;
    std::unordered_map<int, uint8_t> eepromValues;
    std::vector<ParticleEvent> publishedEvents;
    bool alreadyProcessingStateChange;
    bool needToReprocessStateChange;

    void onStateChange();
  };

  extern FakeParticleDevice fakeParticle;
}
