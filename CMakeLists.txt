cmake_minimum_required(VERSION 3.24)

project(
    quixot-project
    VERSION 0.0.2
    DESCRIPTION "A Vulkan graphics engine, made for learning."
    LANGUAGES CXX
)

add_definitions(-DQUIXOT_VERSION_MAJOR=${PROJECT_VERSION_MAJOR})
add_definitions(-DQUIXOT_VERSION_MINOR=${PROJECT_VERSION_MINOR})
add_definitions(-DQUIXOT_VERSION_PATCH=${PROJECT_VERSION_PATCH})
   
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_compile_definitions(
    $<$<CONFIG:Debug>:WITH_DEBUG>
    $<$<NOT:$<CONFIG:Release>>:WITH_DEBUG>
    $<$<CONFIG:Release>:NDEBUG>
)

add_subdirectory(quixot)
add_subdirectory(tests)
add_subdirectory(demo)

