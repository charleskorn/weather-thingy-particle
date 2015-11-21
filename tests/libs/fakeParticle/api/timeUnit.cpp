#include <stdexcept>
#include <string>

#include "timeUnit.hpp"

using namespace std;

namespace FakeParticle {
  uint32_t toMicroseconds(uint32_t time, TimeUnit timeUnit) {
    switch (timeUnit) {
      case TimeUnit::Milliseconds:
        return time * 1000;

      case TimeUnit::Microseconds:
        return time;

      default:
        throw invalid_argument("Unknown timeUnit value: " + to_string(static_cast<int>(timeUnit)));
    }
  }
}
