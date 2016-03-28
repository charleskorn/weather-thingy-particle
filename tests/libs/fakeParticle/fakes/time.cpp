#include "spark_wiring_time.h"
#include "../api/exceptions.hpp"

// From spark_wiring_time.cpp

const char* TIME_FORMAT_DEFAULT = "asctime";
const char* TIME_FORMAT_ISO8601_FULL = "%Y-%m-%dT%H:%M:%S%z";

TimeClass Time;

String TimeClass::format(time_t t, const char* format_spec) {
  throw FakeParticle::NotImplementedException();
}

time_t TimeClass::now() {
  throw FakeParticle::NotImplementedException();
}