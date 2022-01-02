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
  test.Insert(5, 0);
  EXPECT_FALSE(test.Empty());
  test.Insert(3, 0);
  test.Insert(4, 0);
  test.Insert(2, 0);
  test.Insert(7, 0);
  test.Insert(6, 0);
  test.Insert(8, 0);
  EXPECT_TRUE(test.Exists(5));
  EXPECT_TRUE(test.Exists(3));
  EXPECT_TRUE(test.Exists(7));
  EXPECT_TRUE(test.Exists(2));
  EXPECT_TRUE(test.Exists(4));
  EXPECT_TRUE(test.Exists(6));
  EXPECT_TRUE(test.Exists(8));

  test.Insert(5, 2);
  test.Insert(3, 2);
  test.Insert(4, 2);
  test.Insert(2, 2);
  test.Insert(6, 2);
  test.Insert(7, 2);
  test.Insert(8, 2);
}

TEST(AVLTree, NextPrevExisting) {
  AVLTree<int, int> test;
  test.Insert(5, 0);
  test.Insert(3, 0);
  test.Insert(4, 0);
  test.Insert(2, 0);
  test.Insert(7, 0);
  test.Insert(6, 0);
  test.Insert(8, 0);

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
  test.Insert(50, 0);
  test.Insert(30, 0);
  test.Insert(40, 0);
  test.Insert(20, 0);
  test.Insert(70, 0);
  test.Insert(60, 0);
  test.Insert(80, 0);

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

TEST(AVLTree, DeleteLeafs) {
  AVLTree<int, int> test;
  test.Insert(5, 0);
  test.Insert(3, 0);
  test.Insert(4, 0);
  test.Insert(2, 0);
  test.Insert(7, 0);
  test.Insert(6, 0);
  test.Insert(8, 0);

  test.Delete(2);
  EXPECT_FALSE(test.Exists(2));
  test.Delete(4);
  EXPECT_FALSE(test.Exists(4));
  test.Delete(6);
  EXPECT_FALSE(test.Exists(6));
  test.Delete(8);
  EXPECT_FALSE(test.Exists(8));
  test.Delete(3);
  EXPECT_FALSE(test.Exists(3));
  test.Delete(7);
  EXPECT_FALSE(test.Exists(7));
  test.Delete(5);
  EXPECT_FALSE(test.Exists(5));
  EXPECT_TRUE(test.Empty());
}

TEST(AVLTree, DeleteInsideNodesWithLeafMax1) {
  AVLTree<int, int> test;
  test.Insert(50, 0);
  test.Insert(30, 0);
  test.Insert(40, 0);
  test.Insert(20, 0);
  test.Insert(70, 0);
  test.Insert(60, 0);
  test.Insert(80, 0);
  test.Insert(10, 0);
  test.Insert(25, 0);
  test.Insert(35, 0);
  test.Insert(45, 0);
  test.Insert(55, 0);
  test.Insert(65, 0);
  test.Insert(75, 0);
  test.Insert(85, 0);

  test.Delete(30);
  EXPECT_FALSE(test.Exists(30));
  test.Delete(70);
  EXPECT_FALSE(test.Exists(70));
}

TEST(AVLTree, DeleteInsideNodesWithLeafMin) {
  AVLTree<int, int> test;
  test.Insert(50, 0);
  test.Insert(30, 0);
  test.Insert(20, 0);
  test.Insert(70, 0);
  test.Insert(60, 0);
  test.Insert(10, 0);
  test.Insert(25, 0);
  test.Insert(55, 0);
  test.Insert(65, 0);

  test.Delete(30);
  EXPECT_FALSE(test.Exists(30));
  test.Delete(70);
  EXPECT_FALSE(test.Exists(70));
}

TEST(AVLTree, DeleteInsideNodesWithLeafMax2) {
  AVLTree<int, int> test;
  test.Insert(50, 0);
  test.Insert(30, 0);
  test.Insert(40, 0);
  test.Insert(70, 0);
  test.Insert(80, 0);
  test.Insert(35, 0);
  test.Insert(45, 0);
  test.Insert(75, 0);
  test.Insert(85, 0);

  test.Delete(30);
  EXPECT_FALSE(test.Exists(30));
  test.Delete(70);
  EXPECT_FALSE(test.Exists(70));
}

TEST(AVLTree, DeleteInsideNodeNotLeafMax) {
  AVLTree<int, int> test;
  test.Insert(50, 0);
  test.Insert(30, 0);
  test.Insert(40, 0);
  test.Insert(20, 0);
  test.Insert(70, 0);
  test.Insert(60, 0);
  test.Insert(80, 0);
  test.Insert(10, 0);
  test.Insert(25, 0);
  test.Insert(35, 0);
  test.Insert(45, 0);
  test.Insert(55, 0);
  test.Insert(65, 0);
  test.Insert(75, 0);
  test.Insert(85, 0);
  test.Insert(37, 0);

  test.Delete(30);
  EXPECT_FALSE(test.Exists(30));
}

TEST(AVLTree, DeleteInsideNodeNotLeafMin) {
  AVLTree<int, int> test;
  test.Insert(50, 0);
  test.Insert(30, 0);
  test.Insert(20, 0);
  test.Insert(70, 0);
  test.Insert(60, 0);
  test.Insert(80, 0);
  test.Insert(10, 0);
  test.Insert(25, 0);
  test.Insert(55, 0);
  test.Insert(65, 0);
  test.Insert(75, 0);
  test.Insert(85, 0);
  test.Insert(23, 0);

  test.Delete(30);
  EXPECT_FALSE(test.Exists(30));
}

TEST(AVLTree, DeleteLastButOneMax) {
  AVLTree<int, int> test;
  test.Insert(50, 0);
  test.Insert(30, 0);
  test.Insert(40, 0);
  test.Insert(20, 0);
  test.Insert(70, 0);
  test.Insert(60, 0);
  test.Insert(80, 0);

  test.Delete(30);
  EXPECT_FALSE(test.Exists(30));
  test.Delete(70);
  EXPECT_FALSE(test.Exists(70));
  EXPECT_FALSE(test.Exists(45));
}

TEST(AVLTree, DeleteLastButOneMin) {
  AVLTree<int, int> test;
  test.Insert(50, 0);
  test.Insert(30, 0);
  test.Insert(20, 0);
  test.Insert(70, 0);
  test.Insert(60, 0);

  test.Delete(30);
  EXPECT_FALSE(test.Exists(30));
  test.Delete(70);
  EXPECT_FALSE(test.Exists(70));
}

TEST(AVLTree, DeleteHeadBothBranchesFull) {
  AVLTree<int, int> test;
  test.Insert(5, 0);
  test.Insert(3, 0);
  test.Insert(4, 0);
  test.Insert(2, 0);
  test.Insert(7, 0);
  test.Insert(6, 0);
  test.Insert(8, 0);

  test.Delete(5);
  EXPECT_FALSE(test.Exists(5));
  EXPECT_FALSE(test.Empty());
  EXPECT_TRUE(test.Exists(3));
  EXPECT_TRUE(test.Exists(4));
  EXPECT_TRUE(test.Exists(2));
  EXPECT_TRUE(test.Exists(6));
  EXPECT_TRUE(test.Exists(7));
  EXPECT_TRUE(test.Exists(8));
}

TEST(AVLTree, DeleteHeadOnlyLeftBranchPresent) {
  AVLTree<int, int> test;
  test.Insert(5, 0);
  test.Insert(3, 0);
  test.Insert(4, 0);
  test.Insert(2, 0);

  test.Delete(5);
  EXPECT_FALSE(test.Exists(5));
  EXPECT_FALSE(test.Empty());
  EXPECT_TRUE(test.Exists(3));
  EXPECT_TRUE(test.Exists(4));
  EXPECT_TRUE(test.Exists(2));
}

TEST(AVLTree, DeleteHead) {
  AVLTree<int, int> test;
  test.Insert(5, 0);

  test.Delete(5);
  EXPECT_FALSE(test.Exists(5));
  EXPECT_TRUE(test.Empty());
}

TEST(AVLTree, DeleteHeadOnlyOneOnTheLeft) {
  AVLTree<int, int> test;
  test.Insert(5, 0);
  test.Insert(3, 0);

  test.Delete(5);
  EXPECT_FALSE(test.Exists(5));
  EXPECT_FALSE(test.Empty());
  EXPECT_TRUE(test.Exists(3));
}

TEST(AVLTree, DeleteHeadOnlyOneOnTheRight) {
  AVLTree<int, int> test;
  test.Insert(5, 0);
  test.Insert(8, 0);

  test.Delete(5);
  EXPECT_FALSE(test.Exists(5));
  EXPECT_FALSE(test.Empty());
  EXPECT_TRUE(test.Exists(8));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
