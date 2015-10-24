var gulp = require("gulp");

gulp.task("lint", ["lint:firmware", "lint:jshint", "lint:tests"]);
