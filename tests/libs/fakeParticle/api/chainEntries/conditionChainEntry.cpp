#include "conditionChainEntry.hpp"

using namespace std;

namespace FakeParticle {
  ConditionChainEntry::ConditionChainEntry(unique_ptr<Condition> condition) :
    condition(move(condition)) {
  }

  ChainEntryState ConditionChainEntry::reevaluate(FakeParticleDevice& device) {
    if (condition->onTick(device) == ConditionState::Passed) {
      return ChainEntryState::MoveToNext;
    }

    return ChainEntryState::Wait;
  }

  ostream& ConditionChainEntry::describe(ostream& os) const {
    return os << "Wait for condition to be true: " << condition;
  }
}
