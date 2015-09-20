"use strict";

var gulp = require("gulp");
var del = require("del");
var vinylPaths = require("vinyl-paths");
var shell = require("gulp-shell");
var print = require("gulp-print");

var config = require("../config");

gulp.task("setup",
  shell.task([
    "git clone --branch <%= config.particle.firmwareVersion %> --depth 1 --recursive <%= config.particle.firmwareRepository %> <%= config.particle.firmwareDirectory %>"
  ], {
    templateData: {
      config: config
    }
  })
);
