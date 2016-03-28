#pragma once

#include "spark_wiring_string.h"

// From system/inc/system_cloud.h

typedef enum
{
  PUBLIC = 0,
  PRIVATE = 1
} Spark_Event_TypeDef;

typedef int (user_function_int_str_t)(String paramString);

// From wiring/inc/spark_wiring_cloud.h

class CloudClass {
public:
  bool publish(const char *eventName, Spark_Event_TypeDef eventType=PUBLIC);
  bool publish(const char *eventName, const char *eventData, Spark_Event_TypeDef eventType=PUBLIC);

  static bool function(const char *funcKey, user_function_int_str_t* func);
};

extern CloudClass Particle;
