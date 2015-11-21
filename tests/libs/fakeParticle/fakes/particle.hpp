#pragma once

// From system/inc/system_cloud.h

typedef enum
{
  PUBLIC = 0,
  PRIVATE = 1
} Spark_Event_TypeDef;

// From wiring/inc/spark_wiring_cloud.h

class CloudClass {
public:
  bool publish(const char *eventName, Spark_Event_TypeDef eventType=PUBLIC);
  bool publish(const char *eventName, const char *eventData, Spark_Event_TypeDef eventType=PUBLIC);
};

extern CloudClass Particle;
