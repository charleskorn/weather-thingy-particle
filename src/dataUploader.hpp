#pragma once

#include <map>

#include "application.h"
#include "persistentStorage.hpp"

class DataUploader {
public:
  explicit DataUploader(PersistentStorage persistentStorage);

  void uploadData(time_t time, const std::map<String, float>& values) const;

private:
  PersistentStorage persistentStorage;
};
