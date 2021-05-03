#pragma once

#include <gmock/gmock.h>
#include <memory>

template<typename T>
class MockStorage
{
public:
    using value_type = T;
    MOCK_METHOD(bool, insert, (const T&), ());
};

template<typename Mock>
class CopyableMockStorage
{
public:
    using T = typename Mock::value_type;

    bool insert(const T& t) { return mock_->insert(t); }

    Mock& mock() const { return *mock_; }

private:
    std::shared_ptr<Mock> mock_{std::make_shared<Mock>()};
};