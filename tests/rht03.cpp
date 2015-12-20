#include <initializer_list>
#include <stdexcept>

#include "catch.hpp"
#include "fakeParticle.hpp"

#include "rht03.hpp"

static const int DUMMY_SENSOR_PIN = 1;

using namespace FakeParticle;

void addPulsesFromSensor(EventChain& chain, std::initializer_list<bool> pulses);

SCENARIO("RHT03Sensor class") {
  fakeParticle.reset();

  GIVEN("a RHT03 temperature and humidity sensor") {
    RHT03Sensor sensor(DUMMY_SENSOR_PIN);

    WHEN("the driver is initialised") {
      THEN("it sets the pin mode to INPUT") {
        REQUIRE(fakeParticle.getPinMode(DUMMY_SENSOR_PIN) == INPUT);
      }
    }

    WHEN("converting binary temperatures to floating-point numbers") {
      AND_WHEN("the temperature is zero") {
        uint16_t binary = 0;

        THEN("the conversion is performed correctly") {
          REQUIRE(sensor.convertToTemperature(binary) == 0.0f);
        }
      }

      AND_WHEN("the temperature is positive") {
        uint16_t binary = 0b0000000101011111;

        THEN("the conversion is performed correctly") {
          REQUIRE(sensor.convertToTemperature(binary) == 35.1f);
        }
      }

      AND_WHEN("the temperature is negative") {
        uint16_t binary = 0b1000000001100101;

        THEN("the conversion is performed correctly") {
          REQUIRE(sensor.convertToTemperature(binary) == -10.1f);
        }
      }
    }

    WHEN("converting binary relative humidity values to floating-point numbers") {
      AND_WHEN("the relative humidity is zero") {
        uint16_t binary = 0;

        THEN("the conversion is performed correctly") {
          REQUIRE(sensor.convertToHumdity(binary) == 0.0f);
        }
      }

      AND_WHEN("the relative humidity is non-zero") {
        uint16_t binary = 0b0000001010001100;

        THEN("the conversion is performed correctly") {
          REQUIRE(sensor.convertToHumdity(binary) == 65.2f);
        }
      }
    }

    WHEN("validating checksums") {
      AND_WHEN("the received checksum matches the calculated value") {
        uint16_t humidity = 0b0000001010001100;
        uint16_t temperature = 0b0000000101011111;
        uint8_t receivedChecksum = 0b11101110;

        THEN("the data passes the checksum check") {
          REQUIRE(sensor.verifyChecksum(humidity, temperature, receivedChecksum) == true);
        }
      }

      AND_WHEN("the received checksum does not match the calculated value") {
        uint16_t humidity = 0b0000001010001100;
        uint16_t temperature = 0b0000000101011111;
        uint8_t receivedChecksum = 0b11101111;

        THEN("the data fails the checksum check") {
          REQUIRE(sensor.verifyChecksum(humidity, temperature, receivedChecksum) == false);
        }
      }
    }

    WHEN("reading data from the sensor") {
      AND_WHEN("the sensor does not respond during the handshake") {
        EventChain& timeline = fakeParticle
          .immediately(setPin(DUMMY_SENSOR_PIN, HIGH))
          .andThenExpect(pinIsLow(DUMMY_SENSOR_PIN, 1, 10, TimeUnit::Milliseconds))
          .andThenExpect(pinIsHigh(DUMMY_SENSOR_PIN, 20, 40, TimeUnit::Microseconds))
          .andThenExpect(pinModeIs(DUMMY_SENSOR_PIN, INPUT));

        THEN("a timeout error is returned") {
          RHT03SensorData decodedData = sensor.readSensorData();

          REQUIRE(decodedData.timedOut == true);
        }
      }

      AND_WHEN("the sensor stops transmitting during data transmission") {
        EventChain& timeline = fakeParticle
          .immediately(setPin(DUMMY_SENSOR_PIN, HIGH))
          .andThenExpect(pinIsLow(DUMMY_SENSOR_PIN, 1, 10, TimeUnit::Milliseconds))
          .andThenExpect(pinIsHigh(DUMMY_SENSOR_PIN, 20, 40, TimeUnit::Microseconds))
          .andThenExpect(pinModeIs(DUMMY_SENSOR_PIN, INPUT))
          .andThenImmediately(setPin(DUMMY_SENSOR_PIN, LOW))
          .andThenAfter(80, TimeUnit::Microseconds, setPin(DUMMY_SENSOR_PIN, HIGH))
          .andThenWaitFor(80, TimeUnit::Microseconds);

        AND_WHEN("it never pulls the line low after the handshake") {
          THEN("a timeout error is returned") {
            RHT03SensorData decodedData = sensor.readSensorData();

            REQUIRE(decodedData.timedOut == true);
          }
        }

        AND_WHEN("it never pulls the line high") {
          timeline.andThenImmediately(setPin(DUMMY_SENSOR_PIN, LOW));

          THEN("a timeout error is returned") {
            RHT03SensorData decodedData = sensor.readSensorData();

            REQUIRE(decodedData.timedOut == true);
          }
        }

        AND_WHEN("it never pulls the line low after pulling it high") {
          timeline
            .andThenImmediately(setPin(DUMMY_SENSOR_PIN, LOW))
            .andThenAfter(50, TimeUnit::Microseconds, setPin(DUMMY_SENSOR_PIN, HIGH));

          THEN("a timeout error is returned") {
            RHT03SensorData decodedData = sensor.readSensorData();

            REQUIRE(decodedData.timedOut == true);
          }
        }
      }

      AND_WHEN("the sensor transmits data") {
        EventChain& timeline = fakeParticle
          .immediately(setPin(DUMMY_SENSOR_PIN, HIGH))
          .andThenExpect(pinIsLow(DUMMY_SENSOR_PIN, 1, 10, TimeUnit::Milliseconds))
          .andThenExpect(pinIsHigh(DUMMY_SENSOR_PIN, 20, 40, TimeUnit::Microseconds))
          .andThenExpect(pinModeIs(DUMMY_SENSOR_PIN, INPUT))
          .andThenImmediately(setPin(DUMMY_SENSOR_PIN, LOW))
          .andThenAfter(80, TimeUnit::Microseconds, setPin(DUMMY_SENSOR_PIN, HIGH))
          .andThenWaitFor(80, TimeUnit::Microseconds); // Advance the clock to the end of the handshake

        // Set up the waveform described in the datasheet
        // Humidity
        addPulsesFromSensor(timeline, {0, 0, 0, 0});
        addPulsesFromSensor(timeline, {0, 0, 1, 0});
        addPulsesFromSensor(timeline, {1, 0, 0, 0});
        addPulsesFromSensor(timeline, {1, 1, 0, 0});

        // Temperature
        addPulsesFromSensor(timeline, {0, 0, 0, 0});
        addPulsesFromSensor(timeline, {0, 0, 0, 1});
        addPulsesFromSensor(timeline, {0, 1, 0, 1});
        addPulsesFromSensor(timeline, {1, 1, 1, 1});

        // Checksum
        addPulsesFromSensor(timeline, {1, 1, 1, 0});
        addPulsesFromSensor(timeline, {1, 1, 1, 0});

        THEN("the data is received and decoded correctly") {
          RHT03SensorData decodedData = sensor.readSensorData();

          REQUIRE(decodedData.timedOut == false);
          REQUIRE(decodedData.checksumOK == true);
          REQUIRE(decodedData.temperature == 35.1f);
          REQUIRE(decodedData.humidity == 65.2f);
        }
      }
    }
  }

  fakeParticle.assertFinished();
}

void addPulsesFromSensor(EventChain& chain, std::initializer_list<bool> pulses) {
  for (auto pulse = pulses.begin(); pulse != pulses.end(); ++pulse) {
    bool pulseValue = *pulse;
    uint32_t pulseTime = -1;

    if (pulseValue == 0) {
      pulseTime = 27;
    } else if (pulseValue == 1) {
      pulseTime = 70;
    }

    chain
      .andThenImmediately(setPin(DUMMY_SENSOR_PIN, LOW))
      .andThenAfter(50, TimeUnit::Microseconds, setPin(DUMMY_SENSOR_PIN, HIGH))
      .andThenAfter(pulseTime, TimeUnit::Microseconds, setPin(DUMMY_SENSOR_PIN, LOW));
  }
}
