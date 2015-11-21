#include "waitChainEntry.hpp"
#include "../fakeParticleDevice.hpp"

using namespace std;

namespace FakeParticle {
  WaitChainEntry::WaitChainEntry(uint32_t time, TimeUnit timeUnit) :
    haveStartedWaiting(false),
    startedWaitingAt(0)
  {
    timeToWaitInMicroseconds = toMicroseconds(time, timeUnit);
  }

  ChainEntryState WaitChainEntry::reevaluate(FakeParticleDevice& device) {
    if (!haveStartedWaiting) {
      startedWaitingAt = device.getCurrentTimeInMicroseconds();
      haveStartedWaiting = true;
    }

    if (startedWaitingAt + timeToWaitInMicroseconds >= device.getCurrentTimeInMicroseconds()) {
      return ChainEntryState::MoveToNext;
    } else {
      return ChainEntryState::Wait;
    }
  }

  ostream& WaitChainEntry::describe(ostream& os) const {
    // TODO Display this in the original time units

    return os << "Wait for " << timeToWaitInMicroseconds << " microseconds";
  }
}
