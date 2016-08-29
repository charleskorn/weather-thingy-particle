#include "fakeParticleDevice.hpp"
#include "action.hpp"
#include "condition.hpp"
#include "exceptions.hpp"

#include <algorithm>

using namespace std;

namespace FakeParticle {
  FakeParticle::FakeParticleDevice fakeParticle;

  FakeParticleDevice::FakeParticleDevice() {
    reset();
  }

  void FakeParticleDevice::reset() {
    currentTime = 0;
    eventChains.clear();
    pinModes.clear();
    pinDigitalStates.clear();
    pinAnalogValues.clear();
    alreadyProcessingStateChange = false;
    needToReprocessStateChange = false;
  }

  void FakeParticleDevice::assertFinished() {
    for_each(eventChains.begin(), eventChains.end(), [] (const unique_ptr<EventChain>& chain) {
      chain->assertFinished();
    });
  }

  void FakeParticleDevice::setPinMode(uint16_t pin, PinMode mode) {
    pinModes[pin] = mode;

    onStateChange();
  }

  PinMode FakeParticleDevice::getPinMode(uint16_t pin) {
    if (pinModes.find(pin) == pinModes.end()) {
      throw UnknownDeviceStateException("Mode for pin " + to_string(pin) + " has not been set.");
    }

    return pinModes.at(pin);
  }

  void FakeParticleDevice::setPinDigitalState(uint16_t pin, PinState state) {
    pinAnalogValues.erase(pin);
    pinDigitalStates[pin] = state;

    onStateChange();
  }

  PinState FakeParticleDevice::getPinDigitalState(uint16_t pin) {
    if (pinDigitalStates.find(pin) == pinDigitalStates.end()) {
      throw UnknownDeviceStateException("Digital state for pin " + to_string(pin) + " has not been set.");
    }

    return pinDigitalStates.at(pin);
  }

  void FakeParticleDevice::setPinAnalogValue(uint16_t pin, int32_t value) {
    if (value < 0 || value > 4095) {
      throw out_of_range("Analog value " + to_string(value) + " for pin " +
                          to_string(pin) + " is higher than the maximum allowed.");
    }

    pinDigitalStates.erase(pin);
    pinAnalogValues[pin] = value;

    onStateChange();
  }

  int32_t FakeParticleDevice::getPinAnalogValue(uint16_t pin) {
    if (pinAnalogValues.find(pin) == pinAnalogValues.end()) {
      throw UnknownDeviceStateException("Analog value for pin " + to_string(pin) + " has not been set.");
    }

    return pinAnalogValues.at(pin);
  }

  void FakeParticleDevice::setEEPROMValue(int slot, uint8_t value) {
    if (slot < 0 || slot > 2047) {
      throw out_of_range("EEPROM slot " + to_string(slot) + " is not within the range allowed.");
    }

    eepromValues[slot] = value;

    onStateChange();
  }

  uint8_t FakeParticleDevice::getEEPROMValue(int slot) {
    if (eepromValues.find(slot) == eepromValues.end()) {
      throw UnknownDeviceStateException("EEPROM value for slot " + to_string(slot) + " has not been set.");
    }

    return eepromValues.at(slot);
  }

  void FakeParticleDevice::advanceClock(uint32_t microseconds) {
    // Use a for loop rather than just incrementing currentTime directly so that
    // advanceClock(1); advanceClock(1); is exactly the same as advanceClock(2);
    for (uint32_t i = 0; i < microseconds; i++) {
      currentTime++;

      onStateChange();
    }
  }

  uint32_t FakeParticleDevice::getCurrentTimeInMicroseconds() {
    return currentTime;
  }

  EventChain& FakeParticleDevice::after(uint32_t time, TimeUnit timeUnit, Action action) {
    EventChain* chain = new EventChain();
    eventChains.push_back(unique_ptr<EventChain>(chain));

    return chain->andThenAfter(time, timeUnit, action);
  }

  EventChain& FakeParticleDevice::when(Condition* const condition, Action action) {
    EventChain* chain = new EventChain();
    eventChains.push_back(unique_ptr<EventChain>(chain));

    return chain->andThenWhen(condition, action);
  }

  EventChain& FakeParticleDevice::expect(Expectation* const expectation) {
    EventChain* chain = new EventChain();
    eventChains.push_back(unique_ptr<EventChain>(chain));

    return chain->andThenExpect(expectation);
  }

  EventChain& FakeParticleDevice::immediately(Action action) {
    EventChain* chain = new EventChain();
    eventChains.push_back(unique_ptr<EventChain>(chain));

    return chain->andThenImmediately(action);
  }

  void FakeParticleDevice::onStateChange() {
    if (alreadyProcessingStateChange) {
      needToReprocessStateChange = true;
      return;
    }

    alreadyProcessingStateChange = true;

    do {
      needToReprocessStateChange = false;

      for_each(eventChains.begin(), eventChains.end(), [this] (const unique_ptr<EventChain>& chain) {
        chain->onStateChange(*this);
      });
    } while (needToReprocessStateChange);

    alreadyProcessingStateChange = false;
  }
}
