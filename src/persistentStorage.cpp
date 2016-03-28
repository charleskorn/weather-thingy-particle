#include "persistentStorage.hpp"

const int AgentIDBase = 0;
const int TokenBase = AgentIDBase + 4;

void PersistentStorage::saveAgentId(int32_t agentId) const {
	uint8_t first = agentId;
	uint8_t second = agentId >> 8;
	uint8_t third = agentId >> 16;
	uint8_t fourth = agentId >> 24;

	EEPROM.update(AgentIDBase, first);
	EEPROM.update(AgentIDBase + 1, second);
	EEPROM.update(AgentIDBase + 2, third);
	EEPROM.update(AgentIDBase + 3, fourth);
}

int32_t PersistentStorage::getAgentId() const {
	int32_t first = EEPROM.read(AgentIDBase);
	int32_t second = EEPROM.read(AgentIDBase + 1) << 8;
	int32_t third = EEPROM.read(AgentIDBase + 2) << 16;
	int32_t fourth = EEPROM.read(AgentIDBase + 3) << 24;

	return first | second | third | fourth;
}

void PersistentStorage::saveToken(String token) const {
	if (token.length() > getMaxTokenLength()) {
		return;
	}

	EEPROM.update(TokenBase, token.length());

	for (unsigned int i = 0; i < token.length(); i++) {
		EEPROM.update(TokenBase + i + 1, token[i]);
	}
}

String PersistentStorage::getToken() const {
	uint8_t length = EEPROM.read(TokenBase);

	if (length > getMaxTokenLength()) {
		return "";
	}

	String token = "";
	token.reserve(length);

	for (int i = 0; i < length; i++) {
		token += (char)EEPROM.read(TokenBase + i + 1);
	}

	return token;
}

uint32_t PersistentStorage::getMaxTokenLength() const {
	return 63;
}
