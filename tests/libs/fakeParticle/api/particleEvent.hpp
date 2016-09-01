#pragma once

#include "../fakes/particle.hpp"

struct ParticleEvent {
    String name;
    String data;
    Spark_Event_TypeDef type;
};
