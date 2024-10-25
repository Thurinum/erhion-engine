project(core)

add_library(${PROJECT_NAME} STATIC
	io.cpp
	io.h
	logging.h
)
add_library(quixot::core ALIAS ${PROJECT_NAME})
target_precompile_headers(${PROJECT_NAME} PUBLIC 
	pch.h
)
target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_SOURCE_DIR}
)

include(${CMAKE_SOURCE_DIR}/cmake/CompileOptions.cmake)
SET_COMMON_COMPILE_OPTIONS(${PROJECT_NAME})
