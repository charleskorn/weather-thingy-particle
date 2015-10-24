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
          REQUIRE(sensor.convertToTemperature(binary) == 0);
        }
      }
    }
  }
}
