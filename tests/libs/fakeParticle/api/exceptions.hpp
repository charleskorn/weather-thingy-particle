#pragma once

#include <stdexcept>
#include <string>

namespace FakeParticle {
  class NotImplementedException : public std::exception {};

  class AssertionFailedException : public std::exception {
  public:
    explicit AssertionFailedException(std::string message);

    const char* what() const noexcept;

  private:
    std::string message;
  };

  class UnknownDeviceStateException : public std::exception {
  public:
    explicit UnknownDeviceStateException(std::string message);

    const char* what() const noexcept;

  private:
    std::string message;
  };
}
