#pragma once

#include "application.h"
#include "persistentStorage.hpp"

class DataUploader {
public:
  explicit DataUploader(PersistentStorage persistentStorage);

  void uploadData(time_t time, String variableName, float value);

private:
  PersistentStorage persistentStorage;
};
