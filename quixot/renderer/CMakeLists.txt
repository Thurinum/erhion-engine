project(renderer)

add_library(${PROJECT_NAME} STATIC 
    window.cpp
    window.h
#    shader.cpp
 #   shader.h
  #  mesh.cpp
   # mesh.h
)
add_library(quixot::renderer ALIAS ${PROJECT_NAME})

include(FetchContent)
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

find_package(Vulkan REQUIRED)

target_precompile_headers(${PROJECT_NAME} PRIVATE 
    pch.h
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${Vulkan_INCLUDE_DIRS}    
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    quixot::core
    Vulkan::Vulkan
    glfw
)

include(${CMAKE_SOURCE_DIR}/cmake/CompileOptions.cmake)
SET_COMMON_COMPILE_OPTIONS(${PROJECT_NAME})