project(renderer)

add_library(${PROJECT_NAME} SHARED 
    window.cpp
    window.h
    shader.cpp
    shader.h
    mesh.cpp
    mesh.h
)
add_library(quixot::renderer ALIAS ${PROJECT_NAME})

SET_COMMON_COMPILE_OPTIONS(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE
    quixot::core
    GLFW
    glad
    glm_static
)