"use strict";

var gulp = require("gulp");
var shell = require("gulp-shell");

var config = require("../../config");

gulp.task("build:tests", ["build:tests:prepareCMake"],
  shell.task("make install", {
      cwd: config.build.temp.testBuildFiles
    })
);

gulp.task("build:tests:prepareCMake", function() {
  var options = [
    "-D CMAKE_INSTALL_PREFIX=" + config.build.output.tests,
    "-D PARTICLE_FIRMWARE_DIR=" + config.particle.firmwareDirectory,
    "-D CMAKE_BUILD_TYPE=Debug",
    config.build.sources.tests
  ];

  var command = "cmake " + options.join(" ");

  return gulp.src("")
    .pipe(shell("mkdir -p " + config.build.temp.testBuildFiles))
    .pipe(shell(command, {
      cwd: config.build.temp.testBuildFiles
    }));
});
