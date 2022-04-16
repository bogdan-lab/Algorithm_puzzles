#include "gtest/gtest.h"
#include "splay_tree.h"

TEST(SplayTree, EmptyTree) {
  SplayTree<int, int> test;
  EXPECT_TRUE(test.Empty());
  EXPECT_FALSE(test.Find(1));
  EXPECT_FALSE(test.Find(0));
}

TEST(SplayTree, InsertFind1) {
  // Only head
  SplayTree<int, int> test;
  EXPECT_TRUE(test.Empty());
  EXPECT_TRUE(test.Insert(5, 50));
  ASSERT_TRUE(test.Find(5));
  EXPECT_EQ(*test.Find(5), 50);
  EXPECT_FALSE(test.Insert(5, 30));
  ASSERT_TRUE(test.Find(5));
  EXPECT_EQ(*test.Find(5), 50);
}

TEST(SplayTree, InsertFind2) {
  // searching in each cycle in the new tree since it is rebalanced after each
  // search
  std::vector<std::pair<int, int>> input{{1, 10}, {2, 20}, {3, 30}, {4, 40},
                                         {5, 50}, {6, 60}, {7, 70}, {8, 80}};
  int count = 0;
  do {
    count++;
    for (const auto& search_el : input) {
      SplayTree<int, int> test;
      for (const auto& el : input) {
        EXPECT_TRUE(test.Insert(el.first, el.second))
            << "count = " << count << " key = " << el.first << '\n';
      }
      int* res = test.Find(search_el.first);
      ASSERT_TRUE(res) << "count = " << count << " key = " << search_el.first
                       << '\n';
      EXPECT_EQ(*res, search_el.second)
          << "count = " << count << " key = " << search_el.first << '\n';
    }
  } while (std::next_permutation(input.begin(), input.end()));
}

TEST(SplayTree, InsertFind3) {
  // Generate different trees and try to find there each element
  std::vector<std::pair<int, int>> input{{1, 10}, {2, 20}, {3, 30}, {4, 40},
                                         {5, 50}, {6, 60}, {7, 70}, {8, 80}};
  int count = 0;
  do {
    count++;
    SplayTree<int, int> test;
    for (const auto& el : input) {
      EXPECT_TRUE(test.Insert(el.first, el.second))
          << "count = " << count << " key = " << el.first << '\n';
    }
    for (const auto& search_el : input) {
      int* res = test.Find(search_el.first);
      ASSERT_TRUE(res) << "count = " << count << " key = " << search_el.first
                       << '\n';
      EXPECT_EQ(*res, search_el.second)
          << "count = " << count << " key = " << search_el.first << '\n';
    }
  } while (std::next_permutation(input.begin(), input.end()));
}

TEST(SplayTree, InsertFind4) {
  // Create different trees and try to add there elements which are already
  // present there
  std::vector<std::pair<int, int>> input{{1, 10}, {2, 20}, {3, 30}, {4, 40},
                                         {5, 50}, {6, 60}, {7, 70}, {8, 80}};
  int count = 0;
  do {
    count++;
    SplayTree<int, int> test;
    for (const auto& el : input) {
      EXPECT_TRUE(test.Insert(el.first, el.second))
          << "count = " << count << " key = " << el.first << '\n';
    }
    for (const auto& search_el : input) {
      EXPECT_FALSE(test.Insert(search_el.first, search_el.first))
          << "count = " << count << " key = " << search_el.first << '\n';
      EXPECT_FALSE(test.Insert(search_el.first, search_el.second))
          << "count = " << count << " key = " << search_el.first << '\n';
    }
  } while (std::next_permutation(input.begin(), input.end()));
}

TEST(SplayTree, InsertFind5) {
  // Search for absent elements in different trees
  std::vector<std::pair<int, int>> input{{10, 10}, {20, 20}, {30, 30},
                                         {40, 40}, {50, 50}, {60, 60},
                                         {70, 70}, {80, 80}};
  std::vector<int> search_keys{5, 15, 25, 35, 45, 55, 65, 75, 85};
  int count = 0;
  do {
    count++;
    SplayTree<int, int> test;
    for (const auto& el : input) {
      EXPECT_TRUE(test.Insert(el.first, el.second))
          << "count = " << count << " key = " << el.first << '\n';
    }
    for (const auto& key : search_keys) {
      EXPECT_FALSE(test.Find(key))
          << "count = " << count << " key = " << key << '\n';
    }
  } while (std::next_permutation(input.begin(), input.end()));
}

// TODO Delete one element from different trees, check that all other elements
// are present
// TODO Delete all elements from different trees, check that tree is empty at
// the end

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
