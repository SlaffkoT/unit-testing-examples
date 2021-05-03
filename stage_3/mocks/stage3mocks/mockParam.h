#pragma once

#include <gmock/gmock.h>

class MockParam {
public:
  MOCK_METHOD(size_t, getValue, (), (const));
};
