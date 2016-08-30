cmake_minimum_required (VERSION 2.6)
project(weather-thingy-particle-tests)

# Enable warnings, from http://jasonjuang.blogspot.com.au/2014/09/how-to-set-warning-level-in-cmake.html
if(MSVC)
  if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
    string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
  endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

get_filename_component(main_sources_dir ../src ABSOLUTE)

# Important: we're using globbing here, which has limited support in CMake.
# This means that you must explicitly call `cmake` every time a new file is added, otherwise
# it will not detect the change and update the makefiles accordingly.
# This isn't a huge issue for us as the `gulp` task is set to do this every time anyway.
# See http://stackoverflow.com/a/2110796/1668119 for more details.
file(GLOB test_sources *.cpp)
file(GLOB main_sources ${main_sources_dir}/*.cpp)
add_executable(test_runner ${test_sources} ${main_sources})

set_property(TARGET test_runner PROPERTY CXX_STANDARD 14)
set_property(TARGET test_runner PROPERTY CXX_STANDARD_REQUIRED ON)

include_directories(${main_sources_dir})

add_subdirectory(libs)
target_link_libraries(test_runner PUBLIC libs)

install(TARGETS test_runner DESTINATION bin)

# Write a list of all include directories so that cppcheck can use them.
get_property(include_dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
string(REPLACE ";" "\n" formatted_include_dirs "${include_dirs}")
file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/includes_list.txt" ${formatted_include_dirs})
