#pragma once

#include <memory>

#include "../action.hpp"
#include "../condition.hpp"
#include "chainEntry.hpp"

namespace FakeParticle {
  class ConditionChainEntry : public ChainEntry {
  public:
    explicit ConditionChainEntry(std::unique_ptr<Condition> condition);
    ChainEntryState reevaluate(FakeParticleDevice& device);
    std::ostream& describe(std::ostream& os) const;

  private:
    std::unique_ptr<Condition> condition;
  };
}
