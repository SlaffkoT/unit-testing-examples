add_library(stage_1 INTERFACE)
target_include_directories(stage_1 INTERFACE include)

add_subdirectory(tests)
