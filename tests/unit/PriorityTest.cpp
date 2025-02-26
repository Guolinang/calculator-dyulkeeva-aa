#include <gtest/gtest.h>

extern "C" {

int opPriority(int op1, int op2);
}

TEST(TestPrioritry, TestisOP)
{
    int a = '+';
    int b = '*';
    EXPECT_EQ(2, opPriority(a, b)) << "Error in operation priority";
}
