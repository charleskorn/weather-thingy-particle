#include <sstream>
#include <iostream>

#include "condition.hpp"
#include "eventChain.hpp"
#include "exceptions.hpp"
#include "expectations/expectations.hpp"
#include "chainEntries/actionChainEntry.hpp"
#include "chainEntries/conditionChainEntry.hpp"
#include "chainEntries/waitChainEntry.hpp"
#include "fakeParticleDevice.hpp"

using namespace std;

namespace FakeParticle {
  EventChain::EventChain() : currentEntry(chainEntries.begin()) {
  }

  void EventChain::resetCurrentEntry() {
    currentEntry = chainEntries.begin();
  }

  EventChain& EventChain::andThenAfter(uint32_t time, TimeUnit timeUnit, Action action) {
    return this->andThenWaitFor(time, timeUnit).andThenImmediately(action);
  }

  EventChain& EventChain::andThenWaitFor(uint32_t time, TimeUnit timeUnit) {
    chainEntries.push_back(unique_ptr<ChainEntry>(new WaitChainEntry(time, timeUnit)));
    resetCurrentEntry();

    return *this;
  }

  EventChain& EventChain::andThenImmediately(Action action) {
    chainEntries.push_back(unique_ptr<ChainEntry>(new ActionChainEntry(action)));
    resetCurrentEntry();

    return *this;
  }

  EventChain& EventChain::andThenWhen(Condition* const condition, Action action) {
    unique_ptr<Condition> conditionPtr(condition);

    chainEntries.push_back(unique_ptr<ChainEntry>(new ConditionChainEntry(move(conditionPtr))));
    resetCurrentEntry();

    return this->andThenImmediately(action);
  }

  EventChain& EventChain::andThenExpect(Expectation* const expectation) {
    unique_ptr<Condition> expectationPtr(expectation);

    chainEntries.push_back(unique_ptr<ChainEntry>(new ConditionChainEntry(move(expectationPtr))));
    resetCurrentEntry();

    return *this;
  }

  void EventChain::assertFinished() {
    if (chainEntries.empty()) {
      return;
    }

    if (hasReachedEnd()) {
      return;
    }

    ostringstream os;
    os << "Did not reach the end of an event chain. Chain state: " << endl;

    for (vector<std::unique_ptr<ChainEntry>>::const_iterator it = chainEntries.begin(); it < chainEntries.end(); ++it) {
      if (it == currentEntry) {
        os << "  ➔ ";
      } else if (it < currentEntry)
        os << "  ✓ ";
      else {
        os << "    ";
      }

      os << *it << endl;
    }

    throw AssertionFailedException(os.str());
  }

  bool EventChain::hasReachedEnd() {
    return (currentEntry == chainEntries.end());
  }

  void EventChain::onStateChange(FakeParticleDevice& device) {
#ifdef FAKE_PARTICLE_DEBUG
    cout << "Entering onStateChange" << endl;
    cout << " hasReachedEnd: " << hasReachedEnd() << endl;
    cout << " Chain length: " << chainEntries.size() << endl;

    if (!hasReachedEnd()) {
      cout << " Current entry: " << (*currentEntry) << endl;
    }

    cout << " Current time: " << device.getCurrentTimeInMicroseconds() << endl;
#endif

    while (!hasReachedEnd() && (*currentEntry)->reevaluate(device) == ChainEntryState::MoveToNext) {
#ifdef FAKE_PARTICLE_DEBUG
      cout << " Advancing." << endl;
#endif
      ++currentEntry;
    }
  }
}
