#pragma once
#include "application.h"

class TEMT6000Sensor {
public:
  explicit TEMT6000Sensor(int sensorPin);

  float readIlluminance() const;
  double readVoltage() const;
  double convertMeasuredVoltageToCurrent(double voltage) const;
  double convertCurrentToIlluminance(double current) const;

private:
  int sensorPin;
};
