#include "waitChainEntry.hpp"
#include "../fakeParticleDevice.hpp"

using namespace std;

namespace FakeParticle {
  WaitChainEntry::WaitChainEntry(uint32_t time, TimeUnit timeUnit) :
    startedWaitingAt(0),
    haveStartedWaiting(false)
  {
    timeToWaitInMicroseconds = toMicroseconds(time, timeUnit);
  }

  ChainEntryState WaitChainEntry::reevaluate(FakeParticleDevice& device) {
    if (!haveStartedWaiting) {
      startedWaitingAt = device.getCurrentTimeInMicroseconds();
      haveStartedWaiting = true;
    }

    if (device.getCurrentTimeInMicroseconds() >= startedWaitingAt + timeToWaitInMicroseconds) {
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
