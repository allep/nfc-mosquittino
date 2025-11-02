#include <gtest/gtest.h>

#include "StaticContainer.h"

class IElement {
  virtual void DoStuff() = 0;
};

class ConcreteOne : public IElement {
  void DoStuff() override {}
};

TEST(StaticContainerTest, Creation) {
  StaticContainer<IElement, 4> container{};
  EXPECT_EQ(container.Size(), 0);
}

TEST(StaticContainerTest, Add) {
  StaticContainer<IElement, 4> container{};
  auto element{ConcreteOne{}};
  auto res{container.Add(&element)};

  EXPECT_TRUE(res);
  EXPECT_EQ(container.Size(), 1);
}

TEST(StaticContainerTest, AddOverLimit) {
  StaticContainer<IElement, 2> container{};

  auto first{ConcreteOne{}};
  auto second{ConcreteOne{}};
  auto third{ConcreteOne{}};
  auto fourth{ConcreteOne{}};

  EXPECT_TRUE(container.Add(&first));
  EXPECT_TRUE(container.Add(&second));
  EXPECT_FALSE(container.Add(&third));
  EXPECT_FALSE(container.Add(&fourth));

  EXPECT_EQ(container.Size(), 2);
}

TEST(StaticContainerTest, Remove) {
  StaticContainer<IElement, 3> container{};

  auto first{ConcreteOne{}};

  EXPECT_TRUE(container.Add(&first));
  EXPECT_EQ(container.Size(), 1);

  EXPECT_TRUE(container.Remove(&first));
  EXPECT_EQ(container.Size(), 0);
}

TEST(StaticContainerTest, MultipleRemove) {
  StaticContainer<IElement, 3> container{};

  auto first{ConcreteOne{}};

  EXPECT_TRUE(container.Add(&first));
  EXPECT_EQ(container.Size(), 1);

  EXPECT_TRUE(container.Remove(&first));
  EXPECT_FALSE(container.Remove(&first));
}

TEST(StaticContainerTest, MultipleAddAndRemoveSameElement) {
  StaticContainer<IElement, 4> container{};

  auto first{ConcreteOne{}};

  EXPECT_TRUE(container.Add(&first));
  EXPECT_TRUE(container.Add(&first));
  EXPECT_TRUE(container.Add(&first));
  EXPECT_EQ(container.Size(), 3);

  EXPECT_TRUE(container.Remove(&first));
  EXPECT_EQ(container.Size(), 2);

  EXPECT_TRUE(container.Remove(&first));
  EXPECT_EQ(container.Size(), 1);

  EXPECT_TRUE(container.Remove(&first));
  EXPECT_EQ(container.Size(), 0);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
