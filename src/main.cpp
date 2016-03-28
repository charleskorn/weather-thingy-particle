#include "application.h"
#include "rht03.hpp"
#include "temt6000.hpp"

#define TEMP_SENSOR_PIN D6
#define LIGHT_SENSOR_PIN A1

RHT03Sensor temperatureSensor(TEMP_SENSOR_PIN);
TEMT6000Sensor lightSensor(LIGHT_SENSOR_PIN);

void readTemperatureSensorData();
void readLightSensorData();

// cppcheck-suppress unusedFunction Used by Particle framework.
void setup() {
  Particle.publish("wt/node/status", "alive", PRIVATE);

  // Sleep for a second so we don't lose events (see note in readTemperatureSensorData below).
  delay(1000);
}

// cppcheck-suppress unusedFunction Used by Particle framework.
void loop() {
  readTemperatureSensorData();
  readLightSensorData();

  delay(10000);
}

void readTemperatureSensorData() {
  RHT03SensorData result = temperatureSensor.readSensorData();

  // We're not allowed to publish more than 1 event a second
  // (or burst beyond four events in one second with three seconds to recover)
  // See https://docs.particle.io/reference/firmware/photon/#particle-publish-
  if (result.timedOut) {
    Particle.publish("wt/sensors/temperature/status", "Timed out", PRIVATE);
  } else if (!result.checksumOK) {
    Particle.publish("wt/sensors/temperature/status", "Checksum failed", PRIVATE);
  } else {
    Particle.publish("wt/sensors/temperature/status", "OK", PRIVATE);
    Particle.publish("wt/sensors/temperature/humidity", String(result.humidity), PRIVATE);
    Particle.publish("wt/sensors/temperature/temperature", String(result.temperature), PRIVATE);
  }
}

void readLightSensorData() {
  float illuminance = lightSensor.readIlluminance();

  Particle.publish("wt/sensors/light/illuminance", String(illuminance));
}
