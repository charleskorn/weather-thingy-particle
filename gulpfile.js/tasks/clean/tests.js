"use strict";

var gulp = require("gulp");
var shell = require("gulp-shell");
var del = require("del");

var config = require("../../config");
var particleHelpers = require("../../particleHelpers");

gulp.task("clean:tests", ["clean:tests:cmake", "clean:tests:bin"]);

gulp.task("clean:tests:cmake", function () {
  return del([config.build.temp.testBuildFiles + "/**/*"]);
});

gulp.task("clean:tests:bin", function () {
  return del([config.build.output.tests + "/**/*"]);
});
