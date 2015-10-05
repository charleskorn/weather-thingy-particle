"use strict";

var gulp = require("gulp");
var shell = require("gulp-shell");

var config = require("../../config");

gulp.task("build:tests", function() {
  var buildCommands = [
    "cmake -D CMAKE_INSTALL_PREFIX=" + config.build.output.tests + " " + config.build.sources.tests,
    "make",
    "make install"
  ];

  return gulp.src("")
    .pipe(shell("mkdir -p " + config.build.temp.testBuildFiles))
    .pipe(shell(buildCommands, {
      cwd: config.build.temp.testBuildFiles
    }));
});
