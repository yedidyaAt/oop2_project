set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)
if (MSVC)
    add_compile_options (/W4 /permissive- /Zc:externConstexpr /Zc:inline /analyze
        /w14242 /w14263 /w14265 /w14287 /w14296 /w14545 /w14546 /w14547 /w14549
        /w14555 /w14826 /w14905 /w14906 /w14928 /we4996
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
    add_compile_options (
        -Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align
        -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion
        -Wnull-dereference
    )
endif ()
