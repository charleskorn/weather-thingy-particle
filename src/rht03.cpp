#include "rht03.hpp"

RHT03Sensor::RHT03Sensor(int sensorPin) :
  sensorPin(sensorPin) {

}

RHT03SensorData RHT03Sensor::readSensorData() const {
  RHT03SensorData data;
  data.checksumOK = false;

  pinMode(sensorPin, OUTPUT);

  digitalWrite(sensorPin, LOW);
  delay(5); // Wait between 1 and 10 ms

  digitalWrite(sensorPin, HIGH);
  delayMicroseconds(30); // Pull high for 20-40 us

  pinMode(sensorPin, INPUT);

  if (!waitForPinValue(LOW, 80)) {
    // Serial.println("Sensor didn't pull line low!");
    return data;
  }

  if (!waitForPinValue(HIGH, 80)) {
    // Serial.println("Sensor didn't pull line high!");
    return data;
  }

  unsigned long pulseWidths[40];
  unsigned char bits[40];

  for (int i = 39; i >= 0; i--) {
    // Wait for line to go low
    while (digitalRead(sensorPin) != LOW) {}

    // Wait for line to go high
    while (digitalRead(sensorPin) != HIGH) {}

    unsigned long startTime = micros();

    // Wait for line to go low
    while (digitalRead(sensorPin) != LOW) {}

    pulseWidths[i] = micros() - startTime;
  }

  for (int i = 39; i >= 0; i--) {
    if (pulseWidths[i] > 30) {
      bits[i] = 1;
    } else {
      bits[i] = 0;
    }
  }

  uint16_t humidityRaw = read16(bits, 39);
  uint16_t temperatureRaw = read16(bits, 23);
  uint8_t checksum = read8(bits, 7);

  data.humidity = convertToHumdity(humidityRaw);
  data.temperature = convertToTemperature(temperatureRaw);
  data.checksumOK = verifyChecksum(humidityRaw, temperatureRaw, checksum);

  return data;
}

bool RHT03Sensor::waitForPinValue(PinState value, unsigned int timeout) const {
  unsigned long startTime = micros();

  while ((micros() - startTime) < timeout) {
    if (digitalRead(sensorPin) == value) {
      return true;
    }
  }

  return false;
}

uint16_t RHT03Sensor::read16(unsigned char *bits, int start) const {
  uint16_t value = 0;

  for (int i = 0; i < 16; i++) {
    uint16_t bitContribution = bits[start - i] << (15 - i);
    value = value + bitContribution;
  }

  return value;
}

uint8_t RHT03Sensor::read8(unsigned char *bits, int start) const {
  uint8_t value = 0;

  for (int i = 0; i < 8; i++) {
    uint8_t bitContribution = bits[start - i] << (7 - i);
    value = value + bitContribution;
  }

  return value;
}

float RHT03Sensor::convertToTemperature(uint16_t value) const {
  bool isNegative = false;

  if ((value & 0x8000) == 0x8000) {
    isNegative = true;
  }

  value = value & 0x7FFF; // Mask out sign bit

  float temperature = value / 10.0f;

  if (isNegative) {
    temperature = -temperature;
  }

  return temperature;
}

float RHT03Sensor::convertToHumdity(uint16_t value) const {
  return value / 10.0f;
}

bool RHT03Sensor::verifyChecksum(uint16_t humidityRaw, uint16_t temperatureRaw, uint8_t receivedChecksum) const {
  uint8_t part1 = ((humidityRaw & 0xFF00) >> 8);
  uint8_t part2 = humidityRaw & 0x00FF;
  uint8_t part3 = ((temperatureRaw & 0xFF00) >> 8);
  uint8_t part4 = temperatureRaw & 0x00FF;

  uint8_t calculatedChecksum = (part1 + part2 + part3 + part4) & 0xFF;

  return (calculatedChecksum == receivedChecksum);
}