cmake_minimum_required (VERSION 2.6)
project (weather-thingy-particle-tests)

add_executable(test_runner main.cpp)

add_subdirectory(libs)
include_directories(${LIBS_INCLUDE_DIRS})
enable_testing(true)

add_dependencies(test_runner libs)

install (TARGETS test_runner DESTINATION bin)
