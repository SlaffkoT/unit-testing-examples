#include <gtest/gtest.h>

#include "stage_3/Storage.h"

#include "stage3mocks/mockMutex.h"
#include "stage3mocks/mockSet.h"

using ::testing::Exactly;
using ::testing::InSequence;
using ::testing::NiceMock;
using ::testing::Return;
using ::testing::Throw;

class TestStorage : public ::testing::Test
{
protected:
    using Set = CopyableMockSet<MockSet<size_t>>;
    using Mutex = NiceMock<MockMutex>;
    using StorageX = Storage<size_t, Set, Mutex>;

    std::unique_ptr<Mutex> unique_mutex{std::make_unique<Mutex>()};

    Set set;
    Mutex* mutex = unique_mutex.get();
    StorageX storage{set, std::move(unique_mutex)};
};

TEST_F(TestStorage, ConstructorShouldThrowOnNullptrMutex)
{
    std::unique_ptr<Mutex> nullptr_mutex;
    EXPECT_THROW(StorageX(set, std::move(nullptr_mutex)), std::invalid_argument);
}

TEST_F(TestStorage, InsertShouldNotCatchExceptionsOfMutexLock)
{
    EXPECT_CALL(*mutex, lock).WillOnce(Throw(std::exception()));
    EXPECT_CALL(*mutex, unlock).Times(Exactly(0));
    EXPECT_CALL(set.mock(), insert).Times(Exactly(0));
    EXPECT_THROW(storage.insert(1), std::exception);
}

TEST_F(TestStorage, InsertShouldUnlockAfterSetInsertThrows)
{
    EXPECT_CALL(set.mock(), insert).WillOnce(Throw(std::exception()));
    EXPECT_CALL(*mutex, unlock);
    EXPECT_THROW(storage.insert(1), std::exception);
}

TEST_F(TestStorage, InsertShouldCallDepsInSequence)
{
    InSequence s;
    EXPECT_CALL(*mutex, lock).Times(Exactly(1));
    EXPECT_CALL(set.mock(), insert).Times(Exactly(1));
    EXPECT_CALL(*mutex, unlock).Times(Exactly(1));
    storage.insert(1);
}

TEST_F(TestStorage, InsertShouldCallSetInsertWithThePassedValue)
{
    const auto value = 31;
    EXPECT_CALL(set.mock(), insert(value));
    storage.insert(value);
}

TEST_F(TestStorage, InsertShouldReturnSecondOfSetInsertResult)
{
    const auto return1 = std::make_pair(MockSet<size_t>::iterator{}, true);
    const auto return2 = std::make_pair(MockSet<size_t>::iterator{}, false);

    EXPECT_CALL(set.mock(), insert).WillOnce(Return(return1)).WillOnce(Return(return2));
    EXPECT_TRUE(storage.insert(1));
    EXPECT_FALSE(storage.insert(2));
}