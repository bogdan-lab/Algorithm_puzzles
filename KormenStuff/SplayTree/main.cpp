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

TEST(SplayTree, Delete1) {
  struct DelKeyLeft {
    int del_key = 0;
    std::vector<std::pair<int, int>> left;
  };
  // Delete one element from different trees
  std::vector<std::pair<int, int>> input{{1, 10}, {2, 20}, {3, 30}, {4, 40},
                                         {5, 50}, {6, 60}, {7, 70}, {8, 80}};
  std::vector<DelKeyLeft> data = [&input]() {
    std::vector<DelKeyLeft> result(input.size());
    for (size_t i = 0; i < input.size(); ++i) {
      result[i].del_key = input[i].first;
      result[i].left.reserve(input.size() - 1);
      for (size_t j = 0; j < input.size(); ++j) {
        if (i != j) {
          result[i].left.push_back(input[j]);
        }
      }
    }
    return result;
  }();
  int count = 0;
  do {
    count++;
    for (const auto& el : data) {
      SplayTree<int, int> test;
      for (const auto& in_el : input) {
        EXPECT_TRUE(test.Insert(in_el.first, in_el.second))
            << "count = " << count << " key = " << in_el.first << '\n';
      }
      EXPECT_TRUE(test.Delete(el.del_key))
          << "count = " << count << " del_key = " << el.del_key << '\n';
      EXPECT_FALSE(test.Find(el.del_key))
          << "count = " << count << " del_key = " << el.del_key << '\n';
      for (const auto& ch_el : el.left) {
        int* res = test.Find(ch_el.first);
        ASSERT_TRUE(res);
        EXPECT_EQ(*res, ch_el.second);
      }
    }
  } while (std::next_permutation(input.begin(), input.end()));
}

TEST(SplayTree, Delete2) {
  // Delete all elements one by one from different trees
  std::vector<std::pair<int, int>> input{{10, 10}, {20, 20}, {30, 30},
                                         {40, 40}, {50, 50}, {60, 60},
                                         {70, 70}, {80, 80}};
  int count = 0;
  do {
    count++;
    SplayTree<int, int> test;
    for (const auto& el : input) {
      EXPECT_TRUE(test.Insert(el.first, el.second))
          << "count = " << count << " key = " << el.first << '\n';
    }
    for (const auto& key : input) {
      EXPECT_TRUE(test.Delete(key.first))
          << "count = " << count << " key = " << key.first << '\n';
      EXPECT_FALSE(test.Find(key.first))
          << "count = " << count << " key = " << key.first << '\n';
    }
    EXPECT_TRUE(test.Empty());
  } while (std::next_permutation(input.begin(), input.end()));
}

TEST(SplayTree, Delete3) {
  // Delete absent elements from different trees
  std::vector<std::pair<int, int>> input{{10, 10}, {20, 20}, {30, 30},
                                         {40, 40}, {50, 50}, {60, 60},
                                         {70, 70}, {80, 80}};
  std::vector<int> del_keys{5, 15, 25, 35, 45, 55, 65, 75, 85};
  int count = 0;
  do {
    count++;
    SplayTree<int, int> test;
    for (const auto& el : input) {
      EXPECT_TRUE(test.Insert(el.first, el.second))
          << "count = " << count << " key = " << el.first << '\n';
    }
    for (const auto& el : del_keys) {
      EXPECT_FALSE(test.Delete(el))
          << "count = " << count << " key = " << el << '\n';
    }
    for (const auto& el : input) {
      EXPECT_TRUE(test.Find(el.first))
          << "count = " << count << " key = " << el.first << '\n';
    }
  } while (std::next_permutation(input.begin(), input.end()));
}

TEST(SplayTree, Delete4) {
  // Delete element from different trees and then insert it back
  std::vector<std::pair<int, int>> input{{10, 10}, {20, 20}, {30, 30},
                                         {40, 40}, {50, 50}, {60, 60},
                                         {70, 70}, {80, 80}};
  int count = 0;
  do {
    count++;
    for (const auto& op_el : input) {
      SplayTree<int, int> test;
      for (const auto& el : input) {
        EXPECT_TRUE(test.Insert(el.first, el.second))
            << "count = " << count << " key = " << el.first << '\n';
      }
      EXPECT_TRUE(test.Delete(op_el.first))
          << "count = " << count << " key = " << op_el.first << '\n';
      EXPECT_FALSE(test.Find(op_el.first))
          << "count = " << count << " key = " << op_el.first << '\n';
      EXPECT_TRUE(test.Insert(op_el.first, op_el.second))
          << "count = " << count << " key = " << op_el.first << '\n';
      int* res = test.Find(op_el.first);
      ASSERT_TRUE(res) << "count = " << count << " key = " << op_el.first
                       << '\n';
      EXPECT_EQ(*res, op_el.second)
          << "count = " << count << " key = " << op_el.first << '\n';
    }
  } while (std::next_permutation(input.begin(), input.end()));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
