#pragma once

#include <gmock/gmock.h>
#include <memory>

template<typename T>
class MockResultComposer
{
public:
    using value_type = T;
    using return_type = std::pair<bool, T>;

    MOCK_METHOD(return_type, operator_parenthesis, (bool, T), (const));

    auto operator()(bool b, T t) const { return operator_parenthesis(b, t); }
};

template<typename Mock>
class CopyableMockResultComposer
{
public:
    using T = typename Mock::value_type;

    auto operator()(bool b, T t) const { return mock_->operator_parenthesis(b, t); }

    Mock& mock() const { return *mock_; }

private:
    std::shared_ptr<Mock> mock_{std::make_shared<Mock>()};
};