#include "catch.hpp"
#include "fakeParticle.hpp"

#include "temt6000.hpp"

static const int DUMMY_SENSOR_PIN = 1;

using namespace FakeParticle;

SCENARIO("TEMT6000Sensor class") {
  fakeParticle.reset();

  GIVEN("a TEMT6000 ambient light sensor") {
    TEMT6000Sensor sensor(DUMMY_SENSOR_PIN);

    WHEN("the driver is initialised") {
      THEN("it sets the pin mode to INPUT") {
        REQUIRE(fakeParticle.getPinMode(DUMMY_SENSOR_PIN) == INPUT);
      }
    }

    WHEN("the current is 0") {
      THEN("the calculated illuminance should be 0") {
        REQUIRE(sensor.convertCurrentToIlluminance(0) == 0);
      }
    }

    WHEN("the current is 10 uA") {
      THEN("the calculated illuminance should be 20 lux") {
        REQUIRE(sensor.convertCurrentToIlluminance(10e-6) == 20);
      }
    }

    WHEN("the current is 50 uA") {
      THEN("the calculated illuminance should be 100 lux") {
        REQUIRE(sensor.convertCurrentToIlluminance(50e-6) == 100);
      }
    }

    WHEN("the measured voltage is 0 V") {
      THEN("the calculated current should be 0 A") {
        REQUIRE(sensor.convertMeasuredVoltageToCurrent(0) == 0);
      }
    }

    WHEN("the measured voltage is 1 V") {
      THEN("the calculated current should be 100 uA") {
        REQUIRE(sensor.convertMeasuredVoltageToCurrent(1) == 1e-4);
      }
    }

    WHEN("the measured voltage is 3.3 V") {
      THEN("the calculated current should be 330 uA") {
        REQUIRE(sensor.convertMeasuredVoltageToCurrent(3.3) == 3.3e-4);
      }
    }

    WHEN("the analog voltage reading is 0 units") {
      fakeParticle.setPinAnalogValue(DUMMY_SENSOR_PIN, 0);

      THEN("the calculated voltage should be 0 V") {
        REQUIRE(sensor.readVoltage() == 0);
      }

      THEN("the calculated illuminance should be 0 lux") {
        REQUIRE(sensor.readIlluminance() == 0);
      }
    }

    WHEN("the analog voltage reading is 100 units") {
      fakeParticle.setPinAnalogValue(DUMMY_SENSOR_PIN, 100);

      // 100 units = 3.3 * 100 / 4095 V = 0.08059 V
      // 0.08 V gives a current of 8 uA
      // So illuminance should be around 16 lux

      THEN("the calculated voltage should be approximately 0.08059 V") {
        REQUIRE(sensor.readVoltage() == Approx(0.08059));
      }

      THEN("the calculated illuminance should be approximately 16 lux") {
        REQUIRE(sensor.readIlluminance() == Approx(16.1172));
      }
    }

    WHEN("the analog voltage reading is 4095 units") {
      fakeParticle.setPinAnalogValue(DUMMY_SENSOR_PIN, 4095);

      // 4095 units = 3.3 V
      // 3.3 V gives a current of 330 uA
      // So illuminance should be 16 lux

      THEN("the calculated voltage should be 3.3 V") {
        REQUIRE(sensor.readVoltage() == 3.3);
      }

      THEN("the calculated illuminance should be 660 lux") {
        REQUIRE(sensor.readIlluminance() == 660);
      }
    }
  }
}
