"use strict";

var gulp = require("gulp");
var shell = require("gulp-shell");

var config = require("../../config");

// These next two values were found by examining the command line used by Particle's build files.
// They'll almost certainly be wrong if the platform isn't a Photon.
var particleIncludeDirectories = [
  "user/inc",
  "wiring/inc",
  "system/inc",
  "services/inc",
  "communication/lib/tropicssl/include",
  "communication/src",
  "hal/inc",
  "hal/shared",
  "hal/src/photon",
  "hal/src/stm32f2xx",
  "hal/src/stm32",
  // "hal/src/photon/api" -- This one is given on the command line but doesn't actually exist.
  "platform/shared/inc",
  "platform/MCU/STM32F2xx/CMSIS/Include",
  "platform/MCU/STM32F2xx/CMSIS/Device/ST/Include",
  "platform/MCU/STM32F2xx/SPARK_Firmware_Driver/inc",
  "platform/MCU/shared/STM32/inc",
  "platform/MCU/STM32F2xx/STM32_StdPeriph_Driver/inc",
  "platform/MCU/STM32F2xx/STM32_USB_Device_Driver/inc",
  "platform/MCU/STM32F2xx/STM32_USB_Host_Driver/inc",
  "platform/MCU/STM32F2xx/STM32_USB_OTG_Driver/inc",
  "dynalib/inc"
];

var particlePreprocessorSymbols = [
  "STM32_DEVICE",
  "STM32F2XX",
  "PLATFORM_THREADING=1",
  "PLATFORM_ID=6",
  "PLATFORM_NAME=photon",
  "USBD_VID_SPARK=0x2B04",
  "USBD_PID_DFU=0xD006",
  "USBD_PID_CDC=0xC006",
  "SPARK_PLATFORM",
  "INCLUDE_PLATFORM=1",
  "PRODUCT_ID=6",
  "PRODUCT_FIRMWARE_VERSION=65535",
  "USE_STDPERIPH_DRIVER",
  "DFU_BUILD_ENABLE",
  "SYSTEM_VERSION_STRING=0.4.6",
  "RELEASE_BUILD"
];

var particleIncludeArguments = particleIncludeDirectories.map(function(value) {
  return "-I " + config.particle.firmwareDirectory + "/" + value;
});

var particlePreprocessorSymbolArguments = particlePreprocessorSymbols.map(function(value) {
  return "-D" + value;
});

var args = [
  config.lint.cpp.cppcheckOptions,
  config.build.sources.application,
  "--suppress=*:" + config.particle.firmwareDirectory + "/*"
].concat(particleIncludeArguments).concat(particlePreprocessorSymbolArguments);

gulp.task("lint:firmware",
  shell.task(["cppcheck " + args.join(" ")], {
    templateData: {
      config: config
    }
  })
);
