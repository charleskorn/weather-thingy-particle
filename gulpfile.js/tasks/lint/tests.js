var gulp = require("gulp");
var shell = require("gulp-shell");

var config = require("../../config");

var args = [
  config.lint.cpp.cppcheckOptions,
  config.build.sources.tests,
  "--suppress=*:" + config.build.temp.testBuildFiles + "/*", // Exclude warnings from within Catch
  "--suppress=*:" + config.particle.firmwareDirectory + "/*", // Exclude warnings from within Particle firmware files
  "--includes-file=" + config.build.temp.testBuildFiles + "/includes_list.txt",
  "-Dcppcheckdummy" // We don't need to check any preprocessor symbol combinations other than the default.
];

gulp.task("lint:tests", ["build:tests:prepareCMake"],
  shell.task(["cppcheck " + args.join(" ")], {
    templateData: {
      config: config
    }
  })
);
