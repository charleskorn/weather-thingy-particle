#include "catch.hpp"
#include "rht03.hpp"

static const int DUMMY_SENSOR_PIN = 1;

SCENARIO("RHT03Sensor class") {
  GIVEN("a RHT03 temperature and humidity sensor") {
    RHT03Sensor sensor(DUMMY_SENSOR_PIN);

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
  }
}