#include "application.h"
#include "rht03.hpp"

#define TEMP_SENSOR_PIN D6

void readSensorData();

// cppcheck-suppress unusedFunction Used by Particle framework.
void setup() {
  Particle.publish("Starting up");
}

// cppcheck-suppress unusedFunction Used by Particle framework.
void loop() {
  readSensorData();

  delay(10000);
}

void readSensorData() {
  RHT03Sensor sensor(TEMP_SENSOR_PIN);
  RHT03SensorData result = sensor.readSensorData();

  Particle.publish("Timed out?", String(result.timedOut));
  Particle.publish("Checksum OK?", String(result.checksumOK));
  Particle.publish("Humidity", String(result.humidity));
  Particle.publish("Temperature", String(result.temperature));
}
