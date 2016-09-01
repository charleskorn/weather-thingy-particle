var gulp = require("gulp");
var shell = require("gulp-shell");

var config = require("../../config");
var particleHelpers = require("../../particleHelpers");
var targetPath = config.particle.targetName + ".bin";

gulp.task("build:firmware",
  shell.task([
  	"mkdir -p " + config.build.output.firmware,
  	"cd " + config.build.output.firmware + " && rm -f *.bin && particle compile " + config.particle.platform + " " + config.build.sources.application + "/* && " +
  	"echo 'Renaming binary to " + targetPath + "' && mv *.bin " + targetPath
  	], {
    cwd: config.build.output.baseDirectory
  })
);
