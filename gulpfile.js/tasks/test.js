"use strict";

var gulp = require("gulp");
var shell = require("gulp-shell");
var path = require("path");
var watch = require("gulp-watch");
var batch = require("gulp-batch");

var config = require("../config");

var testBinary = path.resolve(config.build.output.tests + "/bin/test_runner");

gulp.task("test", ["build:tests"],
  shell.task(testBinary + " --force-colour")
);

gulp.task("test:watch", ["test"], function () {
  var pathsToWatch = [
    config.build.sources.application + "/**/*",
    config.build.sources.tests + "/**/*"
  ];

  watch(pathsToWatch, batch(function (events, done) {
      gulp.start("test", done);
  }));
});