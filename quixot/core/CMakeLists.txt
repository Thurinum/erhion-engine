project(core)

add_library(${PROJECT_NAME} SHARED
	io.cpp
	io.h
	logging.h
	type_aliases.h
)
add_library(quixot::core ALIAS ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC glm)
SET_COMMON_COMPILE_OPTIONS(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})