project(renderer)

add_library(${PROJECT_NAME} STATIC 
    window.cpp
    window.h
    shader.cpp
    shader.h
    mesh.cpp
    mesh.h
)
add_library(quixot::renderer ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE
    quixot::core
    glfw
    glad
    glm
)

SET_COMMON_COMPILE_OPTIONS(${PROJECT_NAME})