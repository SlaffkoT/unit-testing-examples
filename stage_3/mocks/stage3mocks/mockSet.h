#pragma once

#include <gmock/gmock.h>
#include <set>

template<typename T>
class MockSet
{
public:
    using value_type = T;
    using iterator = typename std::set<T>::iterator;
    using insert_return_type = std::pair<iterator, bool>;

    MOCK_METHOD(insert_return_type, insert, (const T&), ());
};

template<typename Mock>
class CopyableMockSet
{
public:
    using T = typename Mock::value_type;

    auto insert(const T& t) { return mock_->insert(t); }

    Mock& mock() const { return *mock_; }

private:
    std::shared_ptr<Mock> mock_{std::make_shared<Mock>()};
};