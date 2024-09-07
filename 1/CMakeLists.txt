cmake_minimum_required(VERSION 3.13)

project(lab1 VERSION 1 LANGUAGES CXX)

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
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wredundant-decls
        -Wsign-conversion
        -Wsign-promo
)

include_directories(src/include)

add_library(
        core
        src/Car.cpp
        src/CarSerializer.cpp
        src/CarTomlValidator.cpp
        src/IOException.cpp
        src/TestValidator.cpp
        src/ValidationException.cpp
        src/include/AbstractSerializer.hpp
        src/include/AbstractValidator.hpp
        src/include/Car.hpp
        src/include/IOException.hpp
        src/include/TestValidator.hpp
        src/include/ValidationException.hpp
        src/include/CarTomlValidator.hpp
        src/include/CarSerializer.hpp
)

add_executable(main main.cpp)

add_executable(test test/test.cpp)

target_link_libraries(test core gtest)

target_link_libraries(main core)