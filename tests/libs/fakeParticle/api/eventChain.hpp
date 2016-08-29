#pragma once

#include <stdint.h>
#include <vector>
#include <memory>

#include "action.hpp"
#include "timeUnit.hpp"
#include "chainEntries/chainEntry.hpp"

namespace FakeParticle {
  class FakeParticleDevice;
  class Condition;
  class Expectation;

  class EventChain {
  public:
    EventChain();

    EventChain& andThenAfter(uint32_t time, TimeUnit timeUnit, Action action);
    EventChain& andThenWaitFor(uint32_t time, TimeUnit timeUnit);
    EventChain& andThenImmediately(Action action);
    EventChain& andThenWhen(Condition* const condition, Action action);
    EventChain& andThenExpect(Expectation* const expectation);

    void onStateChange(FakeParticleDevice& device);
    void assertFinished();

  private:
    std::vector<std::unique_ptr<ChainEntry>> chainEntries;
    std::vector<std::unique_ptr<ChainEntry>>::iterator currentEntry;

    bool hasReachedEnd();
    void resetCurrentEntry();
  };
}
