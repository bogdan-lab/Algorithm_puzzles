#include "avl_tree.h"
#include "gtest/gtest.h"

TEST(AVLTree, EmptyTree) {
  AVLTree<int, int> test;
  EXPECT_TRUE(test.Empty());
  EXPECT_FALSE(test.Exists(1));
  EXPECT_FALSE(test.Exists(0));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
