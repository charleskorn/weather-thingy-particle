cmake_minimum_required (VERSION 2.6)
project(weather-thingy-particle-tests)

add_subdirectory(libs)

get_filename_component(main_sources_dir ../src ABSOLUTE)

# Important: we're using globbing here, which has limited support in CMake.
# This means that you must explicitly call `cmake` every time a new file is added, otherwise
# it will not detect the change and update the makefiles accordingly.
# This isn't a huge issue for us as the `gulp` task is set to do this every time anyway.
# See http://stackoverflow.com/a/2110796/1668119 for more details.
file(GLOB test_sources *.cpp)
file(GLOB main_sources ${main_sources_dir}/*.cpp)
add_executable(test_runner ${test_sources} ${main_sources})

set_property(TARGET test_runner PROPERTY CXX_STANDARD 11)
set_property(TARGET test_runner PROPERTY CXX_STANDARD_REQUIRED ON)

include_directories(${main_sources_dir})
include_directories(${LIBS_INCLUDE_DIRS})
add_dependencies(test_runner libs)

target_link_libraries(test_runner LINK_PUBLIC fakeParticle)

install(TARGETS test_runner DESTINATION bin)

# Write a list of all include directories so that cppcheck can use them.
get_property(include_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
string(REPLACE ";" "\n" formatted_include_dirs "${include_dirs}")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/includes_list.txt" ${formatted_include_dirs})
