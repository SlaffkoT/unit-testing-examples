cmake_minimum_required(VERSION 3.14)
project(unit-testig-examples)

enable_testing()

include(${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup(TARGETS)

#add_executable(qqq qqq.cpp)

#target_link_libraries(qqq CONAN_PKG::benchmark )

add_subdirectory(stage_1)