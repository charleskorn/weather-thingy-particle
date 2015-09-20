var gulp = require("gulp");
var shell = require("gulp-shell");

var config = require("../../config");
var particleHelpers = require("../../particleHelpers");

gulp.task("clean:firmware",
  shell.task(["make clean" + particleHelpers.commonMakeVariables], {
    cwd: config.particle.firmwareDirectory
  })
);
