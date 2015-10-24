var gulp = require("gulp");
var shell = require("gulp-shell");
var path = require("path");

var config = require("../config");

var testBinary = path.resolve(config.build.output.tests + "/bin/test_runner");

gulp.task("test", ["build:tests"],
  shell.task(testBinary + " --force-colour")
);
