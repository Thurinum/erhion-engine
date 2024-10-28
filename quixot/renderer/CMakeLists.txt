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

# magic enum
FetchContent_Declare(
  magic_enum
  GIT_REPOSITORY https://github.com/Neargye/magic_enum.git
  GIT_TAG v0.9.6
)
FetchContent_MakeAvailable(magic_enum)

find_package(Vulkan REQUIRED)

target_precompile_headers(${PROJECT_NAME} PRIVATE 
    pch.h
)
target_compile_definitions(${PROJECT_NAME} PRIVATE
    GLFW_INCLUDE_VULKAN
    VULKAN_HPP_NO_EXCEPTIONS
    VULKAN_HPP_ASSERT=0
)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_SOURCE_DIR}
    ${Vulkan_INCLUDE_DIRS}    
)
target_link_libraries(${PROJECT_NAME} PRIVATE
    quixot::core
    Vulkan::Vulkan
    glfw
    magic_enum
)

include(${CMAKE_SOURCE_DIR}/cmake/CompileOptions.cmake)
SET_COMMON_COMPILE_OPTIONS(${PROJECT_NAME})