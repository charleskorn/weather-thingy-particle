var gulp = require("gulp");
var shell = require("gulp-shell");

var config = require("../config");
var particleHelpers = require("../particleHelpers");

gulp.task("build",
  shell.task(["make all" + particleHelpers.commonMakeVariables], {
    cwd: config.particle.firmwareDirectory + "/main"
  })
);
