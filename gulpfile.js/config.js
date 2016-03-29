var path = require("path");

var outputDirectory = path.resolve("./output");
var libsDirectory = path.resolve("./libs");
var tempDirectory = path.resolve("./build_temp");

module.exports = {
  particle: {
    platform: "photon", // See https://github.com/spark/firmware/blob/develop/docs/build.md#platform-nameids
    targetName: "weather-thingy-particle", // See https://github.com/spark/firmware/blob/develop/docs/build.md#compiling-an-application-outside-the-firmware-source
    firmwareDirectory: path.resolve(libsDirectory + "/particle/firmware"),
    firmwareRepository: "git@github.com:spark/firmware.git",
    firmwareVersion: "v0.4.7"
  },
  build: {
    sources: {
      application: path.resolve("./src"),
      tests: path.resolve("./tests")
    },
    output: {
      baseDirectory: outputDirectory,
      firmware: outputDirectory + "/firmware",
      tests: outputDirectory + "/tests"
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
