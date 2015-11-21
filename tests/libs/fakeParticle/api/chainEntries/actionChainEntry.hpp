#pragma once

#include "../action.hpp"
#include "chainEntry.hpp"

namespace FakeParticle {
  class ActionChainEntry : public ChainEntry {
  public:
    explicit ActionChainEntry(Action action);
    ChainEntryState reevaluate(FakeParticleDevice& device);
    std::ostream& describe(std::ostream& os) const;

  private:
    Action action;
  };
}
