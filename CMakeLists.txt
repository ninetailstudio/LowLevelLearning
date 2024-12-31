cmake_minimum_required(VERSION 3.10)
project(AssemblyNodes)

# C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Directories
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(INTERFACE_DIR ${CMAKE_SOURCE_DIR}/include/Interfaces)
set(FACTORY_DIR ${CMAKE_SOURCE_DIR}/include/Factories)
set(COMPONENT_DIR ${CMAKE_SOURCE_DIR}/include/Components)
set(EXT_DIR ${CMAKE_SOURCE_DIR}/external)
set(IMGUI_DIR ${EXT_DIR}/imgui)

# Dependencies
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
add_subdirectory(${EXT_DIR}/glm)

# Include directories
include_directories(${INCLUDE_DIR}   ${IMGUI_DIR} ${IMGUI_DIR}/backends ${COMPONENT_DIR})
# ImGui library
set(IMGUI_SOURCES
    ${IMGUI_DIR}/imgui.cpp
    ${IMGUI_DIR}/imgui_demo.cpp
    ${IMGUI_DIR}/imgui_draw.cpp
    ${IMGUI_DIR}/imgui_widgets.cpp
    ${IMGUI_DIR}/imgui_tables.cpp
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC ${IMGUI_DIR} ${IMGUI_DIR}/backends)

# Application sources
set(SOURCES
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Window.cpp
    ${SRC_DIR}/Application.cpp
    ${SRC_DIR}/GUIElements.cpp

    # Add other source files here
)
# Main application
add_executable(imgui_app ${SOURCES})
target_link_libraries(imgui_app PRIVATE imgui glfw GLEW OpenGL::GL dl glm::glm)

# Test sources
set(TEST_SOURCES
    ${CMAKE_SOURCE_DIR}/test/WindowTest.cpp
    ${SRC_DIR}/Window.cpp
)

# Tests
add_executable(WindowTest ${TEST_SOURCES})
target_link_libraries(WindowTest PRIVATE imgui glfw GLEW OpenGL::GL)

# Copy ImGui configuration
if(EXISTS ${CMAKE_SOURCE_DIR}/imgui.ini)
    file(COPY ${CMAKE_SOURCE_DIR}/imgui.ini DESTINATION ${CMAKE_BINARY_DIR})
endif()

# Custom clean-all target
add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}
)
