add_executable(TestStage2 testA.cpp)

target_link_libraries(TestStage2 CONAN_PKG::gtest stage2mocks stage_2)

add_test(NAME TestStage2 COMMAND TestStage2)