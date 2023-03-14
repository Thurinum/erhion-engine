cmake_minimum_required(VERSION 3.24)

project(
        "Erhion Engine"
        VERSION 0.0.1
        DESCRIPTION "A simple game engine."
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)

add_subdirectory(app)