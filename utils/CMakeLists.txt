project(utils)

add_library(${PROJECT_NAME} INTERFACE)
add_library(erhion::utils ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR})