#pragma once
#include "application.h"

struct RHT03SensorData {
  float temperature;
  float humidity;
  bool checksumOK;
  bool timedOut;
};

class RHT03Sensor {
public:
  explicit RHT03Sensor(int sensorPin);

  RHT03SensorData readSensorData() const;
  float convertToTemperature(uint16_t value) const;
  float convertToHumdity(uint16_t value) const;
  bool verifyChecksum(uint16_t humidityRaw, uint16_t temperatureRaw, uint8_t receivedChecksum) const;

private:
  int sensorPin;

  bool waitForPinValue(PinState value, unsigned int timeout) const;

  uint16_t read16(unsigned char *bits, int start) const;
  uint8_t read8(unsigned char *bits, int start) const;
};
