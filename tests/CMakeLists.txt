cmake_minimum_required (VERSION 2.6)
project (weather-thingy-particle-tests)

add_executable(test_runner main.cpp)

install (TARGETS test_runner DESTINATION bin)
