#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <utility>
#include <vector>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace ::testing;

template <typename T>
class CyclicVector {
 public:
  CyclicVector() = default;

  bool Empty() const { return data_.empty(); }
  size_t Size() const { return data_.size(); }
  size_t GetMaxSize() const { return max_size_; }
  const std::vector<T>& GetData() const { return data_; }
  void PushBack(const T& val) { data_.push_back(val); }
  void Shift(int num) {
    num %= data_.size();
    if (num > 0) {
      std::rotate(data_.begin(), data_.begin() + data_.size() - num,
                  data_.end());
    } else if (num < 0) {
      std::rotate(data_.begin(), data_.begin() - num, data_.end());
    }
  }

 private:
  std::vector<T> data_;
  size_t max_size_ = std::numeric_limits<size_t>::max();
};

TEST(CyclicVectorTest, CreatingFromEmptyNoSizeLimits) {
  CyclicVector<int> test;
  EXPECT_TRUE(test.Empty());
  EXPECT_EQ(test.Size(), 0);
  EXPECT_THAT(test.GetMaxSize(), std::numeric_limits<size_t>::max());
  test.PushBack(1);
  test.PushBack(2);
  test.PushBack(3);
  EXPECT_EQ(test.Size(), 3);
  EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3));
}

TEST(CyclicVectorTest, ShiftingWithoutSizeLimits) {
  CyclicVector<int> test;
  test.PushBack(1);
  test.PushBack(2);
  test.PushBack(3);
  test.PushBack(4);
  {
    test.Shift(1);
    EXPECT_THAT(test.GetData(), ElementsAre(4, 1, 2, 3));
    test.Shift(-1);
    EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
  }
  {
    test.Shift(-2);
    EXPECT_THAT(test.GetData(), ElementsAre(3, 4, 1, 2));
    test.Shift(2);
    EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
    test.Shift(-3);
    EXPECT_THAT(test.GetData(), ElementsAre(4, 1, 2, 3));
    test.Shift(3);
    EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
    test.Shift(-4);
    EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
    test.Shift(4);
    EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
    test.Shift(-5);
    EXPECT_THAT(test.GetData(), ElementsAre(2, 3, 4, 1));
    test.Shift(5);
    EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
    test.Shift(-20);
    EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
    test.Shift(20);
    EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
    test.Shift(-101);
    EXPECT_THAT(test.GetData(), ElementsAre(2, 3, 4, 1));
    test.Shift(101);
    EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
