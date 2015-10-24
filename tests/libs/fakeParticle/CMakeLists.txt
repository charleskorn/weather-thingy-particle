project(fakeParticle CXX)

file(GLOB_RECURSE sources *.cpp)
list(APPEND sources ${PARTICLE_FIRMWARE_DIR}/wiring/src/spark_wiring_string.cpp)
list(APPEND sources ${PARTICLE_FIRMWARE_DIR}/wiring/src/spark_wiring_print.cpp)
list(APPEND sources ${PARTICLE_FIRMWARE_DIR}/wiring/src/string_convert.cpp)
set(FAKE_PARTICLE_SOURCES ${sources} CACHE INTERNAL "Path to sources for FakeParticle")

# Includes required for compilation of this library
include_directories(${PARTICLE_FIRMWARE_DIR}/hal/inc)
include_directories(${PARTICLE_FIRMWARE_DIR}/wiring/inc)

# Includes required for consumers of this library (eg. paths to header files referenced in header files)
list(APPEND includes ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND includes ${PARTICLE_FIRMWARE_DIR}/communication/src)
list(APPEND includes ${PARTICLE_FIRMWARE_DIR}/hal/inc)
list(APPEND includes ${PARTICLE_FIRMWARE_DIR}/hal/shared)
list(APPEND includes ${PARTICLE_FIRMWARE_DIR}/services/inc)
list(APPEND includes ${PARTICLE_FIRMWARE_DIR}/system/inc)
list(APPEND includes ${PARTICLE_FIRMWARE_DIR}/wiring/inc)

set(FAKE_PARTICLE_INCLUDE_DIR ${includes} CACHE INTERNAL "Path to include folders for FakeParticle")
