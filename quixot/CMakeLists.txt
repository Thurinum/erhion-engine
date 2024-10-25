project(quixot)

add_subdirectory(core)
add_subdirectory(renderer)

add_library(${PROJECT_NAME} INTERFACE)
add_library(quixot::quixot ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} INTERFACE 
	quixot::core
	quixot::renderer
)