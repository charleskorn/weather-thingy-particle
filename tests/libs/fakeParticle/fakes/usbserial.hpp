#pragma once

#include "spark_wiring_stream.h"

class USBSerial : public Stream
{
public:
  USBSerial();

  unsigned int baud();

  operator bool() { return baud()!=0; }

  void begin(long speed);
  void end();
  int peek();

  virtual size_t write(uint8_t byte);
  virtual int read();
  virtual int availableForWrite();
  virtual int available();
  virtual void flush();

  virtual void blockOnOverrun(bool);

  using Print::write;

private:
  bool _blocking;
};

extern USBSerial Serial;
