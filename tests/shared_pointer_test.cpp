#include "m_memory.hpp"
#include <gtest/gtest.h>

TEST(PtrStatus, PtrIsNull) {
    SharedPtr<int> a;
    EXPECT_EQ(a.get(), nullptr);
}

TEST(PtrStatusNotNull, PtrisNotNull) {
    SharedPtr<int> b(new int(7));
    EXPECT_NE(b.get(), nullptr);
}

