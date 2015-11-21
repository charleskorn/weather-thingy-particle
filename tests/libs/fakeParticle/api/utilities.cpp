#include "utilities.hpp"

using namespace std;

namespace FakeParticle {
  string pinStateToString(PinState state) {
    switch (state) {
      case HIGH:
        return "high";
        break;

      case LOW:
        return "low";
        break;

      default:
        throw out_of_range("Unexpected pin state value: " + to_string(state));
    }
  }

  string pinModeToString(PinMode mode) {
    switch (mode) {
      case INPUT:
        return "input";
        break;

      case OUTPUT:
        return "output";
        break;

      default:
        throw out_of_range("Unexpected pin mode value: " + to_string(mode));
    }
  }
}
