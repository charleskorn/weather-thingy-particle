var gulp = require("gulp");
var shell = require("gulp-shell");
var path = require("path");
var fs = require("fs");

var config = require("../config");
var outputBin = path.resolve(config.build.output.firmware + "/" + config.particle.targetName + ".bin");
var deviceId = null;

try {
    var localConfig = require("../localConfig");
    deviceId = localConfig.particle.deviceId;
}
catch (e) {
    if (!(e instanceof Error && e.code === "MODULE_NOT_FOUND")) {
      throw e;
    }
}

gulp.task("flash-cloud", ["build:firmware"], function() {
	if (deviceId === null) {
		throw "You must create a localConfig.js file and specify the deviceId to use this task.";
	}

	return shell.task(["particle flash " + localConfig.particle.deviceId + " " + outputBin])();
});
