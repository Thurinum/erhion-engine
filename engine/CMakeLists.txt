project(engine)

add_library(${PROJECT_NAME} STATIC window.cpp)
add_library(erhion::engine ALIAS ${PROJECT_NAME})

add_subdirectory(${PROJECT_SOURCE_DIR}/deps/glfw-3.3.8)
add_subdirectory(${PROJECT_SOURCE_DIR}/deps/glad)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME}
        erhion::utils
        glfw
        glad
)