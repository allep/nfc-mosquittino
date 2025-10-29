#include <gtest/gtest.h>

class Foo {
public:
    int getValue() const { return 42; }
    int add(int a, int b) const { return a + b; }
};

// Test fixture (opzionale per test semplici)
class FooTest : public ::testing::Test {
protected:
    Foo foo;
};

// Test che verifica getValue()
TEST_F(FooTest, GetValueReturns42) {
    EXPECT_EQ(foo.getValue(), 42);
}

// Test che verifica add()
TEST_F(FooTest, AddTwoNumbers) {
    EXPECT_EQ(foo.add(2, 3), 5);
    EXPECT_EQ(foo.add(-1, 1), 0);
}

// Test ancora più semplice senza fixture
TEST(FooSimpleTest, BasicTest) {
    Foo foo;
    EXPECT_EQ(foo.getValue(), 42);
}

// main per eseguire i test
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
