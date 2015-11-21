#include "chainEntry.hpp"
#include "../exceptions.hpp"

namespace FakeParticle {
  ChainEntry::ChainEntry() {
  }

  std::ostream& operator<<(std::ostream& os, const std::unique_ptr<ChainEntry>& entry) {
    return entry->describe(os);
  }
}
