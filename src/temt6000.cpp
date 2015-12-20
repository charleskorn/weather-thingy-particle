#include "temt6000.hpp"

TEMT6000Sensor::TEMT6000Sensor(int sensorPin) :
  sensorPin(sensorPin) {
}

float TEMT6000Sensor::readIlluminance() const {
  double measuredVoltage = readVoltage();

  return convertCurrentToIlluminance(convertMeasuredVoltageToCurrent(measuredVoltage));
}

double TEMT6000Sensor::readVoltage() const {
  return 3.3 * analogRead(sensorPin) / 4095;
}

double TEMT6000Sensor::convertCurrentToIlluminance(double current) const {
  return 2e6 * current;
}

double TEMT6000Sensor::convertMeasuredVoltageToCurrent(double voltage) const {
  return voltage / 10e3;
}
