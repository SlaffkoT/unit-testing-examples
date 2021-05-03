#include <gtest/gtest.h>

#include <stage_1/A.h>
#include <stage_1/ParamClass.h>

TEST(A, ShouldReturnProperly)
{
    A a;
    ParamClass p;

    const auto& result1 = a.foo(p);
    const auto& result2 = a.foo(p);

    EXPECT_TRUE(result1.first);
    EXPECT_FALSE(result2.first);
    EXPECT_EQ(result1.second, result2.second);
}