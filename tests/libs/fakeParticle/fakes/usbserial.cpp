#include "spark_wiring_usbserial.h"
#include "../api/exceptions.hpp"

USBSerial Serial;

USBSerial::USBSerial() {
}

void USBSerial::begin(long speed) {
  throw FakeParticle::NotImplementedException();
}

void USBSerial::end() {
  throw FakeParticle::NotImplementedException();
}

int USBSerial::peek() {
  throw FakeParticle::NotImplementedException();
}

size_t USBSerial::write(uint8_t byte) {
  throw FakeParticle::NotImplementedException();
}

int USBSerial::read() {
  throw FakeParticle::NotImplementedException();
}

int USBSerial::available() {
  throw FakeParticle::NotImplementedException();
}

void USBSerial::flush() {
  throw FakeParticle::NotImplementedException();
}
