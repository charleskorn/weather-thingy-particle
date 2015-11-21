var path = require("path");

var baseDirectory = path.resolve("./build");
var tempDirectory = path.resolve("./build_tools");

module.exports = {
  particle: {
    platform: "photon", // See https://github.com/spark/firmware/blob/develop/docs/build.md#platform-nameids
    targetName: "weather-thingy-particle", // See https://github.com/spark/firmware/blob/develop/docs/build.md#compiling-an-application-outside-the-firmware-source
    firmwareDirectory: path.resolve(tempDirectory + "/particle/firmware"),
    firmwareRepository: "git@github.com:spark/firmware.git",
    firmwareVersion: "v0.4.7"
  },
  build: {
    sources: {
      application: path.resolve("./src"),
      tests: path.resolve("./tests")
    },
    output: {
      baseDirectory: baseDirectory,
      firmware: baseDirectory + "/firmware",
      tests: baseDirectory + "/tests"
    },
    temp: {
      baseDirectory: tempDirectory,
      testBuildFiles: tempDirectory + "/tests/build"
    }
  },
  lint: {
    cpp: {
      cppcheckOptions: "--enable=all --inline-suppr" // --check-config is quite handy for making sure that everything is configured correctly but is very noisy
    }
  }
};
