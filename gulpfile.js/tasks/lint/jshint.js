"use strict";

var gulp = require("gulp");
var jshint = require("gulp-jshint");
var stylish = require("jshint-stylish");

gulp.task("lint:jshint", function () {
  return gulp.src("./gulpfile.js/**/*.js")
             .pipe(jshint())
             .pipe(jshint.reporter(stylish))
             .pipe(jshint.reporter("fail"));
});
