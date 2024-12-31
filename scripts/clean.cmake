# Remove the build directory
if(EXISTS "${CMAKE_BINARY_DIR}")
    file(REMOVE_RECURSE ${CMAKE_BINARY_DIR})
endif()

# Optionally, you can also remove the CMakeCache.txt to ensure that there are no cached settings that could mess with the build
if(EXISTS "${CMAKE_BINARY_DIR}/CMakeCache.txt")
    file(REMOVE ${CMAKE_BINARY_DIR}/CMakeCache.txt)
endif()

# Print a message that cleaning was done
message(STATUS "Cleaned up build directory!")
