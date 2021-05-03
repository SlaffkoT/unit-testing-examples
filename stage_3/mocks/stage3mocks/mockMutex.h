#pragma once

#include <gmock/gmock.h>

class MockMutex
{
public:
    MOCK_METHOD(void, lock, (), ());
    MOCK_METHOD(void, unlock, (), ());
};