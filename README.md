# weather-thingy-particle

## Prerequisites

* Local compilation requires:
  * the dependencies listed at [https://github.com/spark/firmware/blob/develop/docs/dependencies.md]()
  * `node` and `npm`
* Testing requires:
  * `cmake` (`brew install cmake` to install)
* `cppcheck` is required for C++ linting (`brew install cppcheck` to install)

## Setup
These commands only need to be run once upon initial clone of the repository or after changes to dependencies.

* Run `npm install`
* Run `gulp setup`

## Building

* Run `gulp build`

## Running

There are two options for flashing your device:

* `gulp flash-cloud` for cloud-based flash, which requires your device to be on and connected to the Particle servers

  In order to use this, you'll need to create `gulpfile.js/localConfig.js` using the following template:

      module.exports = {
        particle: {
          deviceId: "YOUR PARTICLE DEVICE ID HERE"
        }
      };

  replacing `YOUR PARTICLE DEVICE ID HERE` with your device's ID, which you can find by running `particle list`.

* `gulp flash-local` for USB / DFU-based flash, which requires your device to be connected to your computer via USB and
  in [DFU mode](https://docs.particle.io/guide/getting-started/modes/photon/#dfu-mode-device-firmware-upgrade-) (flashing yellow light)

## Testing

* Run `gulp test`

## To do

* Work out how to use .ino files when compiling locally
* Lint (or equivalent) for C++ files
* Travis build

## Notes

* Offline build based on [https://community.particle.io/t/offline-compilation/6260]() and [https://atom.io/packages/particle-offline-compiler]()
