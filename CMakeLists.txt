cmake_minimum_required(VERSION 3.24)

project(
        "Erhion Engine"
        VERSION 0.0.1
        DESCRIPTION "A simple game engine."
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory(app)
add_subdirectory(engine)
add_subdirectory(utils)