var gulp = require("gulp");
var shell = require("gulp-shell");

var config = require("../config");
var particleHelpers = require("../particleHelpers");

// Note: in order for this to work, your device will need to be in DFU mode (flashing yellow light)
// See https://docs.particle.io/guide/getting-started/modes/photon/#dfu-mode-device-firmware-upgrade-
gulp.task("flash-local", ["build:firmware"],
  shell.task(["make program-dfu" + particleHelpers.commonMakeVariables], {
    cwd: config.particle.firmwareDirectory + "/main"
  })
);
