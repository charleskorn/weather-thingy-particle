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
  Particle.publish("Starting up");
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
    Particle.publish("Temperature sensor: status", "Timed out");
  } else if (!result.checksumOK) {
    Particle.publish("Temperature sensor: status", "Checksum failed");
  } else {
    Particle.publish("Temperature sensor: status", "OK");
    Particle.publish("Temperature sensor: humidity", String(result.humidity));
    Particle.publish("Temperature sensor: temperature", String(result.temperature));
  }
}

void readLightSensorData() {
  float illuminance = lightSensor.readIlluminance();

  Particle.publish("Light sensor: illuminance", String(illuminance));
}
