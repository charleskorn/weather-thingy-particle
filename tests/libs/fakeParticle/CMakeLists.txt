project(fakeParticle CXX)

file(GLOB_RECURSE sources *.cpp)
list(APPEND sources ${PARTICLE_FIRMWARE_DIR}/wiring/src/spark_wiring_ipaddress.cpp)
list(APPEND sources ${PARTICLE_FIRMWARE_DIR}/wiring/src/spark_wiring_string.cpp)
list(APPEND sources ${PARTICLE_FIRMWARE_DIR}/wiring/src/spark_wiring_print.cpp)
list(APPEND sources ${PARTICLE_FIRMWARE_DIR}/wiring/src/string_convert.cpp)
add_library(fakeParticle ${sources})

set_property(TARGET fakeParticle PROPERTY CXX_STANDARD 14)
set_property(TARGET fakeParticle PROPERTY CXX_STANDARD_REQUIRED ON)

# Preprocessor definitions required by Particle firmware headers 
target_compile_definitions(fakeParticle PUBLIC RELEASE_BUILD) 
target_compile_definitions(fakeParticle PUBLIC SERVICES_DEBUG_H_) # Work around issue with service_debug.h redefining some (unused) preprocessor macros by pretending that it's already been included

# Includes required for compilation of this library
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${PARTICLE_FIRMWARE_DIR}/hal/inc)
include_directories(${PARTICLE_FIRMWARE_DIR}/hal/shared)
include_directories(${PARTICLE_FIRMWARE_DIR}/services/inc)
include_directories(${PARTICLE_FIRMWARE_DIR}/system/inc)
include_directories(${PARTICLE_FIRMWARE_DIR}/wiring/inc)

# Includes required for consumers of this library
target_include_directories(fakeParticle INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(fakeParticle INTERFACE ${PARTICLE_FIRMWARE_DIR}/communication/src)
target_include_directories(fakeParticle INTERFACE ${PARTICLE_FIRMWARE_DIR}/hal/inc)
target_include_directories(fakeParticle INTERFACE ${PARTICLE_FIRMWARE_DIR}/hal/shared)
target_include_directories(fakeParticle INTERFACE ${PARTICLE_FIRMWARE_DIR}/services/inc)
target_include_directories(fakeParticle INTERFACE ${PARTICLE_FIRMWARE_DIR}/system/inc)
target_include_directories(fakeParticle INTERFACE ${PARTICLE_FIRMWARE_DIR}/wiring/inc)
