var path = require("path");

var baseDirectory = path.resolve("./build");

module.exports = {
  particle: {
    platform: "photon", // See https://github.com/spark/firmware/blob/develop/docs/build.md#platform-nameids
    targetName: "weather-thingy-particle", // See https://github.com/spark/firmware/blob/develop/docs/build.md#compiling-an-application-outside-the-firmware-source
    firmwareDirectory: path.resolve("./build_tools/particle/firmware"),
    firmwareRepository: "git@github.com:spark/firmware.git",
    firmwareVersion: "v0.4.5",
    applicationDirectory: path.resolve("./src")
  },
  build: {
    output: {
      baseDirectory: baseDirectory,
      firmware: baseDirectory + "/firmware"
    }
  }
};
