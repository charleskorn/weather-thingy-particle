#pragma once

#include <map>

#include "application.h"

class DataUploader {
public:
  void uploadData(time_t time, const std::map<String, float>& values) const;

private:
  String constructEventBody(time_t time, const std::map<String, float>& values) const;
  String formatDate(time_t time) const;
};
