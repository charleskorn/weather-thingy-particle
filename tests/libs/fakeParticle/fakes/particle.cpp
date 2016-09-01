#include "particle.hpp"
#include "../api/exceptions.hpp"
#include "fakeParticle.hpp"
#include "../api/particleEvent.hpp"

#include <stdexcept>

using namespace FakeParticle;
using namespace std;

CloudClass Particle;

bool CloudClass::publish(String eventName, Spark_Event_TypeDef eventType) {
	throw FakeParticle::NotImplementedException();
}

bool CloudClass::publish(String eventName, String eventData, Spark_Event_TypeDef eventType) {
  if (eventName.length() > 63) {
    throw out_of_range("Event name must be less than 63 characters.");
  }

  if (eventName.length() < 1) {
    throw out_of_range("Event name must be at least 1 character.");
  }

  if (eventData.length() > 255) {
    throw out_of_range("Event data must not be longer than 255 bytes.");
  }

  ParticleEvent event = {};
  event.name = eventName;
  event.data = eventData;
  event.type = eventType;

  fakeParticle.publishEvent(event);

  return true;
}

bool CloudClass::function(const char *funcKey, user_function_int_str_t* func) {
  throw FakeParticle::NotImplementedException();
}