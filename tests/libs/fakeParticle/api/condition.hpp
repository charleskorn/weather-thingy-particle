#pragma once

#include <string>

#include "pinmap_hal.h"

#include "timeUnit.hpp"

namespace FakeParticle {
  class FakeParticleDevice;

  enum class ConditionState {
    NotYetPassed,
    Passed
  };

  class Condition {
  public:
    virtual ConditionState onTick(FakeParticleDevice& device) = 0;
    virtual std::ostream& describe(std::ostream& os) const = 0;

  protected:
    Condition();
  };

  std::ostream& operator<<(std::ostream& os, const std::unique_ptr<Condition>& entry);
}
