project(quixot-tests)

include(FetchContent)
FetchContent_Declare(
    google_test
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(google_test)

enable_testing()
include(GoogleTest)

function(create_test TEST_NAME TESTED_TARGETS)
    add_executable(${TEST_NAME} ${CMAKE_SOURCE_DIR}/tests/${TEST_NAME}.cpp)
    target_link_libraries(${TEST_NAME} PRIVATE ${TESTED_TARGETS})
    target_link_libraries(${TEST_NAME} PRIVATE gtest_main)
endfunction()

create_test(fake_test quixot::renderer) 
add_test(NAME RipBozoGetBetter COMMAND fake_test)