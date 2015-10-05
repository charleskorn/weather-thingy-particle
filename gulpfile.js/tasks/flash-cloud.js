var gulp = require("gulp");
var shell = require("gulp-shell");
var path = require("path");

var config = require("../config");
var localConfig = require("../localConfig");

var outputBin = path.resolve(config.build.output.firmware + "/" + config.particle.targetName + ".bin");

gulp.task("flash-cloud", ["build:firmware"],
  shell.task(["particle flash " + localConfig.particle.deviceId + " " + outputBin])
);
