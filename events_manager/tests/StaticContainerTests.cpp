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

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
