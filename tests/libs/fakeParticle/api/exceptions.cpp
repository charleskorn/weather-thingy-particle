#include "exceptions.hpp"

namespace FakeParticle {
  AssertionFailedException::AssertionFailedException(std::string message) : message(message) {
  }

  const char* AssertionFailedException::what() const noexcept {
    return message.c_str();
  }

  UnknownDeviceStateException::UnknownDeviceStateException(std::string message) : message(message) {
  }

  const char* UnknownDeviceStateException::what() const noexcept {
    return message.c_str();
  }
}
