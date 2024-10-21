project(core)

add_library(${PROJECT_NAME} STATIC
	io.cpp
	io.h
	logging.h
	type_aliases.h
)
add_library(quixot::core ALIAS ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

SET_COMMON_COMPILE_OPTIONS(${PROJECT_NAME})
