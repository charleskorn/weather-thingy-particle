#include "application.h"

#define TEMP_SENSOR_PIN D6

void readSensorData();
bool waitForPin(int pin, int value, unsigned int timeout);
uint16_t read16(unsigned char *bits, int start);
uint8_t read8(unsigned char *bits, int start);
float convertToTemperature(uint16_t value);
float convertToHumdity(uint16_t value);
void verifyChecksum(uint16_t humidityRaw, uint16_t temperatureRaw, uint8_t receivedChecksum);

void setup() {
  Serial.println("Starting up");
  Spark.publish("Starting up");
}

void loop() {
  Serial.println("Starting to read temperature.");

  readSensorData();

  Serial.println("Done reading temperature.");

  delay(10000);
}

void readSensorData() {
  pinMode(TEMP_SENSOR_PIN, OUTPUT);

  digitalWrite(TEMP_SENSOR_PIN, LOW);
  delay(5); // Wait between 1 and 10 ms

  digitalWrite(TEMP_SENSOR_PIN, HIGH);
  delayMicroseconds(30); // Pull high for 20-40 us

  pinMode(TEMP_SENSOR_PIN, INPUT);

  if (!waitForPin(TEMP_SENSOR_PIN, LOW, 80)) {
    Serial.println("Sensor didn't pull line low!");
    return;
  }

  if (!waitForPin(TEMP_SENSOR_PIN, HIGH, 80)) {
    Serial.println("Sensor didn't pull line high!");
    return;
  }

  unsigned long pulseWidths[40];
  unsigned char bits[40];

  for (int i = 39; i >= 0; i--) {
    // Wait for line to go low
    while (digitalRead(TEMP_SENSOR_PIN) != LOW) {}

    // Wait for line to go high
    while (digitalRead(TEMP_SENSOR_PIN) != HIGH) {}

    unsigned long startTime = micros();

    // Wait for line to go low
    while (digitalRead(TEMP_SENSOR_PIN) != LOW) {}

    pulseWidths[i] = micros() - startTime;
  }

  for (int i = 39; i >= 0; i--) {
    // Serial.print(i, DEC);
    // Serial.print(" ");
    // Serial.println(pulseWidths[i]);

    if (pulseWidths[i] > 30) {
      bits[i] = 1;
    } else {
      bits[i] = 0;
    }
  }

  uint16_t humidityRaw = read16(bits, 39);
  uint16_t temperatureRaw = read16(bits, 23);
  uint8_t checksum = read8(bits, 7);

  float humidity = convertToHumdity(humidityRaw);
  float temperature = convertToTemperature(temperatureRaw);

  Serial.print("Humidity: ");
  Serial.println(humidity);

  Serial.print("Temperature: ");
  Serial.println(temperature);

  verifyChecksum(humidityRaw, temperatureRaw, checksum);

  Spark.publish("Humidity", String(humidity));
  Spark.publish("Temperature", String(temperature));
}

bool waitForPin(int pin, int value, unsigned int timeout) {
  unsigned long startTime = micros();

  while ((micros() - startTime) < timeout) {
    if (digitalRead(pin) == value) {
      return true;
    }
  }

  return false;
}

uint16_t read16(unsigned char *bits, int start) {
  uint16_t value = 0;

  for (int i = 0; i < 16; i++) {
    uint16_t bitContribution = bits[start - i] << (15 - i);
    value = value + bitContribution;
  }

  return value;
}

uint8_t read8(unsigned char *bits, int start) {
  uint8_t value = 0;

  for (int i = 0; i < 8; i++) {
    uint8_t bitContribution = bits[start - i] << (7 - i);
    value = value + bitContribution;
  }

  return value;
}

float convertToTemperature(uint16_t value) {
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

float convertToHumdity(uint16_t value) {
  return value / 10.0f;
}

void verifyChecksum(uint16_t humidityRaw, uint16_t temperatureRaw, uint8_t receivedChecksum) {
  uint8_t part1 = ((humidityRaw & 0xFF00) >> 8);
  uint8_t part2 = humidityRaw & 0x00FF;
  uint8_t part3 = ((temperatureRaw & 0xFF00) >> 8);
  uint8_t part4 = temperatureRaw & 0x00FF;

  uint8_t calculatedChecksum = (part1 + part2 + part3 + part4) & 0xFF;

  if (calculatedChecksum == receivedChecksum) {
    Serial.println("Checksum OK");
    Spark.publish("Checksum", "OK");
  } else {
    Serial.println("Checksum not OK!");
    Spark.publish("Checksum", "Not OK");
  }
}
