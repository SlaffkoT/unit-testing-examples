#include <gtest/gtest.h>

#include "stage_3/A.h"
#include "stage_3/Storage.h"

TEST(IntegrationA, ShouldReturnProperly)
{
    auto composer = [](auto x, auto y) { return std::make_pair(x, y); };
    Storage<size_t, std::set<size_t>, std::mutex> storage;

    A<size_t, decltype(composer)> a{std::move(composer)};

    ParamClass p;

    const auto& result1 = a.foo(p);
    const auto& result2 = a.foo(p);

    EXPECT_TRUE(result1.first);
    EXPECT_FALSE(result2.first);
    EXPECT_EQ(result1.second, result2.second);
}