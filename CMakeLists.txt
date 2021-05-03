cmake_minimum_required(VERSION 3.14)
project(unit-testig-examples)

enable_testing()

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

add_compile_options(-Wall
                    -Wextra
                    -Wshadow
                    -Wnon-virtual-dtor
                    -Wold-style-cast
                    -Wcast-align
                    -Wunused
                    -Woverloaded-virtual
                    -Wconversion
                    -fstack-protector-strong)

add_subdirectory(stage_1)
add_subdirectory(stage_2)
add_subdirectory(stage_3)