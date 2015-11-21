#pragma once

#include "../action.hpp"
#include "../timeUnit.hpp"
#include "chainEntry.hpp"

namespace FakeParticle {
  class WaitChainEntry : public ChainEntry {
  public:
    explicit WaitChainEntry(uint32_t time, TimeUnit timeUnit);
    ChainEntryState reevaluate(FakeParticleDevice& device);
    std::ostream& describe(std::ostream& os) const;

  private:
    uint32_t timeToWaitInMicroseconds;
    uint32_t startedWaitingAt;
    bool haveStartedWaiting;
  };
}
