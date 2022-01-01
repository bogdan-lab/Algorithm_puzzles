#include "avl_tree.h"
#include "gtest/gtest.h"

TEST(AVLTree, EmptyTree) {
  AVLTree<int, int> test;
  EXPECT_TRUE(test.Empty());
  EXPECT_FALSE(test.Exists(1));
  EXPECT_FALSE(test.Exists(0));
}

TEST(AVLTree, InsertExists) {
  AVLTree<int, int> test;
  EXPECT_TRUE(test.Empty());
  EXPECT_TRUE(test.Insert(5, 0));
  EXPECT_FALSE(test.Empty());
  EXPECT_TRUE(test.Insert(3, 0));
  EXPECT_TRUE(test.Insert(4, 0));
  EXPECT_TRUE(test.Insert(2, 0));
  EXPECT_TRUE(test.Insert(7, 0));
  EXPECT_TRUE(test.Insert(6, 0));
  EXPECT_TRUE(test.Insert(8, 0));
  EXPECT_TRUE(test.Exists(5));
  EXPECT_TRUE(test.Exists(3));
  EXPECT_TRUE(test.Exists(7));
  EXPECT_TRUE(test.Exists(2));
  EXPECT_TRUE(test.Exists(4));
  EXPECT_TRUE(test.Exists(6));
  EXPECT_TRUE(test.Exists(8));
}

TEST(AVLTree, NextPrevExisting) {
  AVLTree<int, int> test;
  EXPECT_TRUE(test.Insert(5, 0));
  EXPECT_TRUE(test.Insert(3, 0));
  EXPECT_TRUE(test.Insert(4, 0));
  EXPECT_TRUE(test.Insert(2, 0));
  EXPECT_TRUE(test.Insert(7, 0));
  EXPECT_TRUE(test.Insert(6, 0));
  EXPECT_TRUE(test.Insert(8, 0));

  EXPECT_EQ(test.Prev(5)->key, 4);
  EXPECT_EQ(test.Next(5)->key, 6);
  EXPECT_EQ(test.Prev(3)->key, 2);
  EXPECT_EQ(test.Next(3)->key, 4);
  EXPECT_EQ(test.Prev(7)->key, 6);
  EXPECT_EQ(test.Next(7)->key, 8);
  EXPECT_EQ(test.Prev(8)->key, 7);
  EXPECT_FALSE(test.Next(8));
  EXPECT_FALSE(test.Next(100));
  EXPECT_FALSE(test.Prev(2));
  EXPECT_FALSE(test.Prev(-50));
  EXPECT_EQ(test.Next(2)->key, 3);
}

TEST(AVLTree, NextPrevNonexisting) {
  AVLTree<int, int> test;
  EXPECT_TRUE(test.Insert(50, 0));
  EXPECT_TRUE(test.Insert(30, 0));
  EXPECT_TRUE(test.Insert(40, 0));
  EXPECT_TRUE(test.Insert(20, 0));
  EXPECT_TRUE(test.Insert(70, 0));
  EXPECT_TRUE(test.Insert(60, 0));
  EXPECT_TRUE(test.Insert(80, 0));

  EXPECT_EQ(test.Prev(45)->key, 40);
  EXPECT_EQ(test.Next(45)->key, 50);
  EXPECT_EQ(test.Prev(55)->key, 50);
  EXPECT_EQ(test.Next(55)->key, 60);
  EXPECT_EQ(test.Prev(35)->key, 30);
  EXPECT_EQ(test.Next(35)->key, 40);
  EXPECT_EQ(test.Prev(65)->key, 60);
  EXPECT_EQ(test.Next(65)->key, 70);
  EXPECT_EQ(test.Prev(25)->key, 20);
  EXPECT_EQ(test.Next(25)->key, 30);
  EXPECT_EQ(test.Prev(75)->key, 70);
  EXPECT_EQ(test.Next(75)->key, 80);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
