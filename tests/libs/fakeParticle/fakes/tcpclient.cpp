#include "spark_wiring_tcpclient.h"
#include "../api/exceptions.hpp"

TCPClient::TCPClient() {
  throw FakeParticle::NotImplementedException();
}

int TCPClient::connect(IPAddress ip, uint16_t port, network_interface_t interface) {
  throw FakeParticle::NotImplementedException();
}

int TCPClient::connect(const char *host, uint16_t port, network_interface_t interface) {
  throw FakeParticle::NotImplementedException();
}

size_t TCPClient::write(uint8_t) {
  throw FakeParticle::NotImplementedException();
}

size_t TCPClient::write(const uint8_t *buffer, size_t size) {
  throw FakeParticle::NotImplementedException();
}

int TCPClient::available() {
  throw FakeParticle::NotImplementedException();
}

int TCPClient::read() {
  throw FakeParticle::NotImplementedException();
}

int TCPClient::read(uint8_t *buffer, size_t size) {
  throw FakeParticle::NotImplementedException();
}

int TCPClient::peek() {
  throw FakeParticle::NotImplementedException();
}

void TCPClient::flush() {
  throw FakeParticle::NotImplementedException();
}

void TCPClient::stop() {
  throw FakeParticle::NotImplementedException();
}

uint8_t TCPClient::connected() {
  throw FakeParticle::NotImplementedException();
}

TCPClient::operator bool() {
  throw FakeParticle::NotImplementedException();
}

IPAddress TCPClient::remoteIP() {
  throw FakeParticle::NotImplementedException();
}
