#include "catch.hpp"
#include "fakeParticle.hpp"

#include "dataUploader.hpp"

using namespace FakeParticle;
using namespace std;

SCENARIO("DataUploader class") {
  fakeParticle.reset();

  GIVEN("a data uploader") {
    DataUploader uploader;

    WHEN("data is uploaded") {
      time_t time = 1472618589; // Wed, 31 Aug 2016 04:43:09 UTC
      std::map<String, float> data;
      data["first"] = 4.56789;
      data["second"] = 1.234567;

      uploader.uploadData(time, data);

      THEN("exactly one Particle event should be published") {
        REQUIRE(fakeParticle.getPublishedEvents().size() == 1);
      }

      THEN("the event should have the correct name") {
        REQUIRE(fakeParticle.getPublishedEvents().front().name == "wt/data");
      }

      THEN("the event should be private") {
        REQUIRE(fakeParticle.getPublishedEvents().front().type == PRIVATE);
      }

      THEN("the event should contain the exepcted data") {
        REQUIRE(fakeParticle.getPublishedEvents().front().data == "{\"date\":\"2016-08-31T04:43:09Z\",\"first\":4.567890,\"second\":1.234567}");
      }
    }
  }
}
