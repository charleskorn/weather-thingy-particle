#include "actionChainEntry.hpp"

using namespace std;

namespace FakeParticle {
  ActionChainEntry::ActionChainEntry(Action action) : action(action) {
  }

  ChainEntryState ActionChainEntry::reevaluate(FakeParticleDevice& device) {
    action(device);

    return ChainEntryState::MoveToNext;
  }

  ostream& ActionChainEntry::describe(ostream& os) const {
    // TODO Get description from action

    return os << "Perform action";
  }
}
