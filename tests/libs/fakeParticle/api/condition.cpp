#include "condition.hpp"

using namespace std;

namespace FakeParticle {
  Condition::Condition() {
  }

  ostream& operator<<(ostream& os, const unique_ptr<Condition>& entry) {
    return entry->describe(os);
  }
}
