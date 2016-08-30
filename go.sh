#! /usr/bin/env bash

set -e

SOURCE_ROOT_DIRECTORY="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
IMAGE="charleskorn/particle-docker-dev-env:latest"

function main {
  case "$1" in

  setup)
    setup
    ;;

  gulp)
    runGulp "${@:2}"
    ;;

  run)
    runOtherCommand "${@:2}"
    ;;

  *)
    help
    exit 1
    ;;

  esac
}

function help {
  echo "Usage:"
  echo " setup          downloads and installs any missing dependencies (apart from Docker, which must already be configured)"
  echo " gulp <params>  runs Gulp with the parameters given inside a build container"
  echo " run <command>  runs the command given inside a build container"
  exit -1
}

function setup {
  docker pull $IMAGE
  runInDockerContainer npm install
}

function runGulp {
  runInDockerContainer "./node_modules/.bin/gulp" "$@"
}

function runOtherCommand {
  runInDockerContainer "$@"
}

function runInDockerContainer {
  docker run -it --rm \
    --volume $SOURCE_ROOT_DIRECTORY:/source \
    --volume $HOME/.particle:/root/.particle \
    --workdir /source \
    $IMAGE \
    "$@"
}

main "$@"
