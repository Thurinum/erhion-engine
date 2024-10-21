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

include_directories(quixot)
include_directories(thirdparty)
include_directories(thirdparty/glfw/include)
include_directories(thirdparty/glad/include)

add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glad)
add_subdirectory(thirdparty/glm)

add_subdirectory(quixot/core)
add_subdirectory(quixot/renderer)
add_subdirectory(demo)