#include "dataUploader.hpp"

void DataUploader::uploadData(time_t time, const std::map<String, float>& values) const {
  Particle.publish("wt/data", constructEventBody(time, values), PRIVATE);
}

String DataUploader::constructEventBody(time_t time, const std::map<String, float>& values) const {
  String formattedTime = formatDate(time);
  String eventBody = "{\"date\":\"" + formattedTime + "\",";
  size_t valuesSeenSoFar = 0;

  for (auto iterator = values.begin(); iterator != values.end(); iterator++) {
    eventBody += "\"" + iterator->first + "\":" + String(iterator->second);
    valuesSeenSoFar++;

    if (valuesSeenSoFar < values.size()) {
      eventBody += ",";
    }
  }

  eventBody += "}";

  return eventBody;
}

// We can't use Time.format() here because it throws an exception when running on the host (eg. during testing).
String DataUploader::formatDate(time_t time) const {
  tm* timeDetails = localtime(&time);
  char buffer[50];
  strftime(buffer, sizeof(buffer), "%Y-%m-%dT%H:%M:%SZ", timeDetails);

  return String(buffer);
}
