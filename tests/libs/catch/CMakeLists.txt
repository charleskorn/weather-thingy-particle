# From https://github.com/philsquared/Catch/blob/master/docs/build-systems.md#cmake

cmake_minimum_required(VERSION 2.8.8)
project(catch CXX)
include(ExternalProject)
find_package(Git REQUIRED)

ExternalProject_Add(
    catch_sources
    PREFIX ${CMAKE_BINARY_DIR}/catch
    GIT_REPOSITORY https://github.com/philsquared/Catch.git
    TIMEOUT 10
    UPDATE_COMMAND ${GIT_EXECUTABLE} pull
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
    LOG_DOWNLOAD ON
   )

ExternalProject_Get_Property(catch_sources source_dir)

add_library(catch INTERFACE)
add_dependencies(catch catch_sources)
target_include_directories(catch INTERFACE ${source_dir}/include)
