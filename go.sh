#! /usr/bin/env bash

set -e

SOURCE_ROOT_DIRECTORY="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

function main {
  case "$1" in

  setup)
    setup
    ;;

  versionInfo)
    versionInfo
    ;;

  gulp)
    runGulp "${@:2}"
    ;;

  *)
    help
    exit 1
    ;;

  esac
}

function help {
  echo "Usage:"
  echo " TODO"
  exit -1
}

function setup {
  echo "TODO"
  exit -1
}

function runGulp {
  runInDockerContainer "./node_modules/.bin/gulp" "$@"
}

function versionInfo {
  runInDockerContainer cmake --version
}

function runInDockerContainer {
  docker run -it --rm \
    --volume $SOURCE_ROOT_DIRECTORY:/source \
    --volume $HOME/.particle:/root/.particle \
    --workdir /source \
    weather-thingy-build:latest \
    "$@"
}

main "$@"
