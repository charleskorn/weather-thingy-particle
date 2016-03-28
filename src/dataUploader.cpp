#include "dataUploader.hpp"

DataUploader::DataUploader(PersistentStorage persistentStorage) :
  persistentStorage(persistentStorage) {
}

void DataUploader::uploadData(time_t time, String variableName, float value) {
  String formattedTime = Time.format(time, TIME_FORMAT_ISO8601_FULL);
  String requestBody = "{\"time\":\"" + formattedTime + "\", \"data\":[{\"variable\":\"" + variableName + "\", \"value\":" + String(value) + "}]}";

  byte server[] = {10, 0, 0, 14};

  TCPClient client;

  if (client.connect(server, 8000))
  {
    Serial.println("Connected.");

    String agentId = String(persistentStorage.getAgentId());
    String token = persistentStorage.getToken();

    client.println("POST /v1/agents/" + agentId + "/data HTTP/1.1");
    client.println("User-Agent: weather-thingy-particle");
    client.println("Connection: close");
    client.println("Authorization: weather-thingy-agent-token " + token);
    client.println("Accept: */*");
    client.println("Content-Type: application/json");
    client.println("Content-Length: " + String(requestBody.length()));
    client.println();
    client.println(requestBody);
    client.println();

    client.flush();

    Serial.println("Response:");

    // TODO Check response indicates success

    unsigned long startTime = micros();

    while (micros() - startTime < 2 * 1000 * 1000) {
      while (client.available()) {
        Serial.write(client.read());
      }
    }

    Serial.println();
    Serial.println("End of response.");

    client.stop();
  }
  else
  {
    Serial.println("Connection failed!");
  }
}