set(GLOBAL_HEADER_PATH "${CMAKE_SOURCE_DIR}/quixot/core/type_aliases.h")

function (set_common_compile_options target)
    if (MSVC)
        target_compile_options(${target} PRIVATE
            /W4
            /WX   # warnings as errors
            /permissive- # conformant mode
            /FI${GLOBAL_HEADER_PATH}

            $<$<CONFIG:Debug>:
                /Zi        # debug info
                /Od        # no optimization
                /analyze   # static analysis
            >
        )
    else()
        target_compile_options(${target} PRIVATE
            -Wall 
            -Wextra 
            -Werror
            -include ${GLOBAL_HEADER_PATH}

            $<$<CONFIG:Debug>:
                -O0  # no optimization
                -g   # debug info
                -fsanitize=address 
                -fsanitize=undefined 
                -fno-exceptions
                -pedantic
            >
        )
    endif()
endfunction()