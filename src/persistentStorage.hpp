#pragma once
#include "application.h"

class PersistentStorage {
public:
	void saveAgentId(int32_t id) const;
	int32_t getAgentId() const;

	void saveToken(String token) const;
	String getToken() const;

	uint32_t getMaxTokenLength() const;
};