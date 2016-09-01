#include "application.h"
#include "rht03.hpp"
#include "temt6000.hpp"
#include "dataUploader.hpp"

#define TEMP_SENSOR_PIN D6
#define LIGHT_SENSOR_PIN A1

RHT03Sensor temperatureSensor(TEMP_SENSOR_PIN);
TEMT6000Sensor lightSensor(LIGHT_SENSOR_PIN);
DataUploader dataUploader;

void readTemperatureSensorData(std::map<String, float>& values);
void readLightSensorData(std::map<String, float>& values);

// cppcheck-suppress unusedFunction Used by Particle framework.
void setup() {
  Particle.publish("wt/node/status", "alive", PRIVATE);

  // Sleep for a second so we don't lose events (see note in readTemperatureSensorData below).
  delay(1000);
}

// cppcheck-suppress unusedFunction Used by Particle framework.
void loop() {
  time_t time = Time.now();
  std::map<String, float> values;

  readTemperatureSensorData(values);
  readLightSensorData(values);

  dataUploader.uploadData(time, values);

  delay(10000);
}

void readTemperatureSensorData(std::map<String, float>& values) {
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

    values["temperature"] = result.temperature;
    values["humidity"] = result.humidity;
  }
}

void readLightSensorData(std::map<String, float>& values) {
  values["illuminance"] = lightSensor.readIlluminance();
}