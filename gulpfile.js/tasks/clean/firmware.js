"use strict";

var gulp = require("gulp");
var shell = require("gulp-shell");
var del = require("del");

var config = require("../../config");
var particleHelpers = require("../../particleHelpers");

gulp.task("clean:firmware", ["clean:firmware:make", "clean:firmware:bin"]);

gulp.task("clean:firmware:make",
  shell.task(["make clean" + particleHelpers.commonMakeVariables], {
    cwd: config.particle.firmwareDirectory
  })
);

gulp.task("clean:firmware:bin", function () {
  return del([config.build.output.firmware + "/**/*"]);
});
