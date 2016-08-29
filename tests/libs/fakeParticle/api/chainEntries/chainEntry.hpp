#pragma once

#include <ostream>
#include <memory>

namespace FakeParticle {
  class FakeParticleDevice;

  enum class ChainEntryState {
    Wait,
    MoveToNext
  };

  class ChainEntry {
  public:
    virtual ChainEntryState reevaluate(FakeParticleDevice& device) = 0;
    virtual std::ostream& describe(std::ostream& os) const = 0;

  protected:
    ChainEntry();
  };

  std::ostream& operator<<(std::ostream& os, const std::unique_ptr<ChainEntry>& entry);
}
