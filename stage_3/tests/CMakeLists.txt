add_executable(TestStage3 testA.cpp testStorage.cpp testIntegration.cpp)

target_link_libraries(TestStage3 CONAN_PKG::gtest stage3mocks stage_3)

add_test(NAME TestStage3 COMMAND TestStage3)