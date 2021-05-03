add_library(stage_2 INTERFACE)
target_include_directories(stage_2 INTERFACE include)

add_subdirectory(tests)
add_subdirectory(mocks)
