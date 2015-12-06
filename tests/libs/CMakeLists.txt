add_library(libs INTERFACE)

# Add all dependencies in this directory. Assumes all subdirectories are dependencies and that each subdirectory
# contains a CMakeLists.txt that defines a target with the same name as the directory.
# (eg. blahLib/CMakeLists.txt defines a library target called blahLib)

file(GLOB children *)

foreach(child ${children})
    if(IS_DIRECTORY ${child})
      add_subdirectory(${child})
      get_filename_component(dependency_name ${child} NAME)
      target_link_libraries(libs INTERFACE ${dependency_name})
    endif()
endforeach()
