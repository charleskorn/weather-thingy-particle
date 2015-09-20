"use strict";

var config = require("./config");
var _ = require("lodash");

function commonMakeVariables() {
  var variables = {
    "PLATFORM": config.particle.platform,
    "APPDIR": config.particle.applicationDirectory,
    "TARGET_DIR": config.build.output.firmware,
    "TARGET_FILE": config.particle.targetName
  };

  return " " + _.map(variables, function(value, key) { return key + "=" + value; }).join(" ");
}

module.exports = {
  commonMakeVariables: commonMakeVariables()
};
