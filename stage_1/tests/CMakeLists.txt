add_executable(TestStage1 testA.cpp)

target_link_libraries(TestStage1 CONAN_PKG::gtest stage_1)

add_test(NAME TestStage1 COMMAND TestStage1)