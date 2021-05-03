add_library(stage_3 INTERFACE)
target_include_directories(stage_3 INTERFACE include)

add_subdirectory(tests)
add_subdirectory(mocks)
