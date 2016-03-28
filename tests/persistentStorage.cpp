#include "catch.hpp"
#include "fakeParticle.hpp"

#include "persistentStorage.hpp"

using namespace FakeParticle;

SCENARIO("PersistentStorage class") {
  fakeParticle.reset();

  const int agentIdBaseSlot = 0;
  const int tokenBaseSlot = 4;

  GIVEN("a storage device") {
    PersistentStorage storage;

    WHEN("an agent ID is saved") {
      THEN("it is stored in EEPROM") {
        storage.saveAgentId(0x12345678);

        REQUIRE(fakeParticle.getEEPROMValue(agentIdBaseSlot) == 0x78);
        REQUIRE(fakeParticle.getEEPROMValue(agentIdBaseSlot + 1) == 0x56);
        REQUIRE(fakeParticle.getEEPROMValue(agentIdBaseSlot + 2) == 0x34);
        REQUIRE(fakeParticle.getEEPROMValue(agentIdBaseSlot + 3) == 0x12);
      }
    }

    WHEN("an agent ID is retrieved") {
      THEN("it returns the ID stored in EEPROM") {
        fakeParticle.setEEPROMValue(agentIdBaseSlot, 0x78);
        fakeParticle.setEEPROMValue(agentIdBaseSlot + 1, 0x56);
        fakeParticle.setEEPROMValue(agentIdBaseSlot + 2, 0x34);
        fakeParticle.setEEPROMValue(agentIdBaseSlot + 3, 0x12);

        REQUIRE(storage.getAgentId() == 0x12345678);
      }
    }

    WHEN("an agent ID is saved and then retrieved") {
      THEN("the value retrieved is the same as the value saved") {
        int32_t agentId = 0x12345678;

        storage.saveAgentId(agentId);

        REQUIRE(storage.getAgentId() == agentId);
      }
    }

    WHEN("a token is saved") {
      THEN("it is stored in EEPROM") {
        storage.saveToken("token123");

        REQUIRE(fakeParticle.getEEPROMValue(tokenBaseSlot) == 8);
        REQUIRE(fakeParticle.getEEPROMValue(tokenBaseSlot + 1) == 't');
        REQUIRE(fakeParticle.getEEPROMValue(tokenBaseSlot + 2) == 'o');
        REQUIRE(fakeParticle.getEEPROMValue(tokenBaseSlot + 3) == 'k');
        REQUIRE(fakeParticle.getEEPROMValue(tokenBaseSlot + 4) == 'e');
        REQUIRE(fakeParticle.getEEPROMValue(tokenBaseSlot + 5) == 'n');
        REQUIRE(fakeParticle.getEEPROMValue(tokenBaseSlot + 6) == '1');
        REQUIRE(fakeParticle.getEEPROMValue(tokenBaseSlot + 7) == '2');
        REQUIRE(fakeParticle.getEEPROMValue(tokenBaseSlot + 8) == '3');
      }
    }

    WHEN("a token is retrieved") {
      THEN("it returns the value stored in EEPROM") {
        fakeParticle.setEEPROMValue(tokenBaseSlot, 8);
        fakeParticle.setEEPROMValue(tokenBaseSlot + 1, 't');
        fakeParticle.setEEPROMValue(tokenBaseSlot + 2, 'o');
        fakeParticle.setEEPROMValue(tokenBaseSlot + 3, 'k');
        fakeParticle.setEEPROMValue(tokenBaseSlot + 4, 'e');
        fakeParticle.setEEPROMValue(tokenBaseSlot + 5, 'n');
        fakeParticle.setEEPROMValue(tokenBaseSlot + 6, '1');
        fakeParticle.setEEPROMValue(tokenBaseSlot + 7, '2');
        fakeParticle.setEEPROMValue(tokenBaseSlot + 8, '3');

        REQUIRE(storage.getToken() == "token123");
      }
    }

    WHEN("a token is saved and then retrieved") {
      THEN("the value retrieved is the same as the value saved") {
        storage.saveToken("token123");

        REQUIRE(storage.getToken() == "token123");
      }
    }
  }
}