# weather-thingy-particle

## Prerequisites

* Local compilation requires:
  * the dependencies listed at [https://github.com/spark/firmware/blob/develop/docs/dependencies.md]()
  * `node` and `npm`

## Setup
These commands only need to be run once upon initial clone of the repository or after changes to dependencies.

* Run `npm install`
* Run `gulp setup`

## Building

* Run `gulp build`

## Running

* Flash device using either:
  * `gulp flash-cloud` for cloud-based flash: requires your device to be on and connected to the Particle servers
  * `gulp flash-local` for USB / DFU-based flash: requires your device to be connected to your computer via USB and
    in [DFU mode](https://docs.particle.io/guide/getting-started/modes/photon/#dfu-mode-device-firmware-upgrade-)  (flashing yellow light)

## To do

* Work out how to use .ino files when compiling locally

## Notes

* Offline build based on [https://community.particle.io/t/offline-compilation/6260]() and [https://atom.io/packages/particle-offline-compiler]()
