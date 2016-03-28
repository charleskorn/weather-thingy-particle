#include "application.h"
#include "rht03.hpp"
#include "temt6000.hpp"
#include "persistentStorage.hpp"
#include "dataUploader.hpp"

#define TEMP_SENSOR_PIN D6
#define LIGHT_SENSOR_PIN A1

RHT03Sensor temperatureSensor(TEMP_SENSOR_PIN);
TEMT6000Sensor lightSensor(LIGHT_SENSOR_PIN);
PersistentStorage persistentStorage;
DataUploader dataUploader(persistentStorage);

void readTemperatureSensorData();
void readLightSensorData();
int setAgentId(String agentId);
int setToken(String token);

// cppcheck-suppress unusedFunction Used by Particle framework.
void setup() {
  Particle.publish("wt/node/status", "alive", PRIVATE);

  // Sleep for a second so we don't lose events (see note in readTemperatureSensorData below).
  delay(1000);

  Particle.function("setAgentId", setAgentId);
  Particle.function("setToken", setToken);
}

int setAgentId(String agentId) {
  int32_t convertedId = agentId.toInt();

  if (convertedId == 0) {
    return -1;
  }

  persistentStorage.saveAgentId(convertedId);
  return 0;
}

int setToken(String token) {
  if (token.length() > persistentStorage.getMaxTokenLength()) {
    return -1;
  }

  persistentStorage.saveToken(token);
  return 0;
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

    time_t time = Time.now();

    dataUploader.uploadData(time, "temperature", result.temperature);
    dataUploader.uploadData(time, "humidity", result.humidity);
  }
}

void readLightSensorData() {
  float illuminance = lightSensor.readIlluminance();

  Particle.publish("wt/sensors/light/illuminance", String(illuminance));

  dataUploader.uploadData(Time.now(), "illuminance", illuminance);
}