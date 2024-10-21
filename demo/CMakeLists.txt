project(app)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} quixot::renderer)

set(FILES_TO_MOVE
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/simple.vs"
    "${CMAKE_CURRENT_SOURCE_DIR}/shaders/simple.fs"
)

# Define a custom command to move the files after building the target
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMAND ${CMAKE_COMMAND} -E copy ${FILES_TO_MOVE} $<TARGET_FILE_DIR:${PROJECT_NAME}>
    COMMENT "Moving resource files to the executable directory..."
)