cmake_minimum_required(VERSION 3.13)

project(lab2 VERSION 1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

if (NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif ()

add_compile_options(
        -Werror
        -Wall
        -Wextra
        -Wpedantic
        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wenum-compare
        -Wfloat-equal
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
)

include_directories(src/core/include)

include_directories(src/io/include)

add_library(
        io
        src/io/IOException.cpp
        src/io/include/IOException.hpp
        src/io/include/Utils.hpp
        src/io/Utils.cpp
)

add_library(
        core
        src/core/InvalidStateException.cpp
        src/core/include/InvalidStateException.hpp
        src/core/Resource.cpp
        src/core/include/Resource.hpp
        src/core/ResourceTable.cpp
        src/core/include/ResourceTable.hpp
)


add_executable(main main.cpp)

add_executable(test test/test.cpp)

target_link_libraries(main core io)

target_link_libraries(test core io gtest -lgcov -fprofile-arcs -ftest-coverage --coverage)