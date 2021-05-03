#include <gtest/gtest.h>

#include "stage_2/A.h"

#include "stage2mocks/mockParam.h"
#include "stage2mocks/mockResultComposer.h"
#include "stage2mocks/mockStorage.h"

using ::testing::Exactly;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Throw;

class TestA : public ::testing::Test
{
protected:
    TestA()
    {
        ON_CALL(param, getValue).WillByDefault(Return(value));
        ON_CALL(storage.mock(), insert).WillByDefault(Return(true));
        ON_CALL(composer.mock(), operator_parenthesis).WillByDefault(Return(result));
    }

    using Storage = CopyableMockStorage<MockStorage<size_t>>;
    using Composer = CopyableMockResultComposer<MockResultComposer<size_t>>;

    Storage storage;
    Composer composer;
    NiceMock<MockParam> param;
    A<size_t, Composer, Storage> a{composer, storage};

    const size_t value{87};
    const std::pair<bool, size_t> result{std::make_pair(true, value)};
};

TEST_F(TestA, ShouldNotCatchExceptionsOfGetValue)
{
    EXPECT_CALL(param, getValue).WillOnce(Throw(std::exception()));
    EXPECT_CALL(storage.mock(), insert).Times(Exactly(0));
    EXPECT_CALL(composer.mock(), operator_parenthesis).Times(Exactly(0));
    EXPECT_THROW(a.foo(param), std::exception);
}

TEST_F(TestA, ShouldNotCatchExceptionsOfStorageInsert)
{
    EXPECT_CALL(param, getValue);
    EXPECT_CALL(storage.mock(), insert).WillOnce(Throw(std::exception()));
    EXPECT_CALL(composer.mock(), operator_parenthesis).Times(Exactly(0));
    EXPECT_THROW(a.foo(param), std::exception);
}

TEST_F(TestA, ShouldNotCatchExceptionsOfResultComposer)
{
    EXPECT_CALL(param, getValue);
    EXPECT_CALL(storage.mock(), insert);
    EXPECT_CALL(composer.mock(), operator_parenthesis).WillOnce(Throw(std::exception()));
    EXPECT_THROW(a.foo(param), std::exception);
}

TEST_F(TestA, ShouldCallDepsInSequence)
{
    InSequence in;
    EXPECT_CALL(param, getValue);
    EXPECT_CALL(storage.mock(), insert);
    EXPECT_CALL(composer.mock(), operator_parenthesis);
    EXPECT_NO_THROW(a.foo(param));
}

TEST_F(TestA, ShouldCallStorageInsertWithValueReturnedByGetValue)
{
    EXPECT_CALL(param, getValue);
    EXPECT_CALL(storage.mock(), insert(value));
    EXPECT_CALL(composer.mock(), operator_parenthesis);
    EXPECT_NO_THROW(a.foo(param));
}

TEST_F(TestA, ShouldCallComposerWithResultOfStorageAndValue)
{
    EXPECT_CALL(param, getValue);
    EXPECT_CALL(storage.mock(), insert);
    EXPECT_CALL(composer.mock(), operator_parenthesis(true, value));
    EXPECT_NO_THROW(a.foo(param));
}

TEST_F(TestA, ShouldReturnResultOfComposer)
{
    EXPECT_CALL(param, getValue);
    EXPECT_CALL(storage.mock(), insert);
    EXPECT_CALL(composer.mock(), operator_parenthesis).WillOnce(Return(result));
    EXPECT_EQ(a.foo(param), result);
}