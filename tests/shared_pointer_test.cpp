#include "m_memory.hpp"
#include <gtest/gtest.h>

TEST(SharedPtrTest, PtrIsNull) {
    SharedPtr<int> a;
    EXPECT_EQ(a.get(), nullptr);
}

TEST(SharedPtrTest, PtrisNotNull) {
    SharedPtr<int> b(new int(7));
    EXPECT_NE(b.get(), nullptr);
}

TEST(SharedPtrTest, IsCounting) {
    SharedPtr<int> a(new int(7));
    EXPECT_EQ(a.use_count(), 1);
    SharedPtr<int> b(a);
    EXPECT_EQ(a.use_count(), 2);
    EXPECT_EQ(b.use_count(), 2);
}

TEST(SharedPtrTest, CpyAssign_SharesOwnership) {
    SharedPtr<int> a(new int(10));
    SharedPtr<int> b;

    b=a;

    EXPECT_EQ(a.use_count(), 2);
    EXPECT_EQ(b.use_count(), 2);
    EXPECT_EQ(b.get(), a.get());

}

TEST(SharedPtrTest, MoveConstructor) {

    SharedPtr<int> a(new int(10));
    auto tempPtr = a.get();
    auto b = std::move(a);

    EXPECT_EQ(a.use_count(), 0);
    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(b.use_count(), 1);
    EXPECT_EQ(b.get(), tempPtr);
}

TEST(SharedPtrTest, DefaultRelease) {
    SharedPtr<int> a(new int(10));
    a.release();
    EXPECT_EQ(a.get(), nullptr);
    EXPECT_EQ(a.use_count(), 0);
}

TEST(SharedPtrTest, ReleaseAndAquire) {
    SharedPtr<int> a(new int(10));
    auto tempPtr = a.get();
    a.release(new int(15));
    EXPECT_NE(a.get(), tempPtr);
    EXPECT_EQ(a.use_count(), 1);
}
