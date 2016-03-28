#include "particle.hpp"
#include "../api/exceptions.hpp"

CloudClass Particle;

bool CloudClass::publish(const char *eventName, Spark_Event_TypeDef eventType) {
	throw FakeParticle::NotImplementedException();
}

bool CloudClass::publish(const char *eventName, const char *eventData, Spark_Event_TypeDef eventType) {
  throw FakeParticle::NotImplementedException();
}

bool CloudClass::function(const char *funcKey, user_function_int_str_t* func) {
  throw FakeParticle::NotImplementedException();
}