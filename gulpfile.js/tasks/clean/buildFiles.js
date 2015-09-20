"use strict";

var gulp = require("gulp");
var del = require("del");

var config = require("../../config");

gulp.task("clean:buildFiles", function () {
  return del([config.build.output.firmware + "/**/*"]);
});
