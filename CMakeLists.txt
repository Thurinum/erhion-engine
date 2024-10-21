cmake_minimum_required(VERSION 3.24)

project(
    "Quixot Engine"
    VERSION 0.0.2
    DESCRIPTION "A useless game engine."
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(cmake/CompileFlags.cmake)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "Do not build shared lib" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Do not build examples" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Do not build tests" FORCE)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Do not build the GLFW docs" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "Do not install GLFW on system" FORCE)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glm)
include_directories(thirdparty/glfw/include)
include_directories(thirdparty/glad/include)
include_directories(thirdparty/glm)

add_subdirectory(quixot/core)
add_subdirectory(quixot/renderer)
add_subdirectory(demo)