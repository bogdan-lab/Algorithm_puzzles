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
  CyclicVector(size_t max_size) : max_size_(max_size) {}

  bool Empty() const { return data_.empty(); }

  size_t Size() const { return data_.size(); }

  size_t GetMaxSize() const { return max_size_; }

  const std::vector<T>& GetData() {
    Flatten();
    return data_;
  }

  void PushBack(const T& val) {
    if (max_size_ == 0) return;
    if (Size() < max_size_) {
      if (!(begin_idx_ == 0)) {
        Flatten();
      }
      data_.push_back(val);
    } else {
      data_[begin_idx_] = val;
      Shift(-1);
    }
  }

  void Shift(int num) {
    if (Empty()) return;
    num %= static_cast<int>(Size());
    begin_idx_ += num >= 0 ? Size() - num : -num;
    begin_idx_ %= Size();
  }

  void SetMaxSize(size_t val) {
    if (max_size_ == val) return;
    if (Size() <= val) {
      max_size_ = val;
    } else if (Size() > val) {
      int redundant_num = Size() - val;
      Shift(-redundant_num);
      Flatten();
      while (redundant_num--) {
        data_.pop_back();
      }
      max_size_ = val;
    }
  }

 private:
  void Flatten() {
    std::rotate(data_.begin(), data_.begin() + begin_idx_, data_.end());
    begin_idx_ = 0;
  }

  std::vector<T> data_;
  size_t max_size_ = std::numeric_limits<size_t>::max();
  size_t begin_idx_ = 0;
};

TEST(CyclicVectorTest, CreatingFromEmptyNoSizeLimits) {
  CyclicVector<int> test;
  EXPECT_TRUE(test.Empty());
  EXPECT_EQ(test.Size(), 0);
  EXPECT_THAT(test.GetMaxSize(), std::numeric_limits<size_t>::max());
  test.PushBack(1);
  test.PushBack(2);
  test.PushBack(3);
  EXPECT_FALSE(test.Empty());
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
    test.Shift(0);
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

TEST(CyclicVectorTest, ShiftingVectorWithSizeOne) {
  CyclicVector<int> test(1);
  EXPECT_TRUE(test.Empty());
  EXPECT_EQ(test.Size(), 0);
  test.PushBack(1);
  test.Shift(0);
  EXPECT_THAT(test.GetData(), ElementsAre(1));
  test.Shift(-1);
  EXPECT_THAT(test.GetData(), ElementsAre(1));
  test.Shift(1);
  EXPECT_THAT(test.GetData(), ElementsAre(1));
  test.Shift(-100);
  EXPECT_THAT(test.GetData(), ElementsAre(1));
  test.Shift(100);
  EXPECT_THAT(test.GetData(), ElementsAre(1));
}

TEST(CyclicVectorTest, ShiftingEmptyVector) {
  {
    CyclicVector<int> test;
    EXPECT_TRUE(test.Empty());
    EXPECT_EQ(test.Size(), 0);
    test.Shift(1);
    test.Shift(-1);
    test.Shift(0);
    test.Shift(1000);
    EXPECT_TRUE(test.Empty());
    EXPECT_EQ(test.Size(), 0);
  }
  {
    CyclicVector<int> test(1);
    EXPECT_TRUE(test.Empty());
    EXPECT_EQ(test.Size(), 0);
    test.Shift(1);
    test.Shift(-1);
    test.Shift(0);
    test.Shift(1000);
    EXPECT_TRUE(test.Empty());
    EXPECT_EQ(test.Size(), 0);
  }
}

TEST(CyclicVectorTest, FillingVectorWithSizeRestriction) {
  CyclicVector<int> test(4);
  EXPECT_TRUE(test.Empty());
  EXPECT_EQ(test.Size(), 0);
  EXPECT_EQ(test.GetMaxSize(), 4);
  test.PushBack(1);
  test.PushBack(2);
  test.PushBack(3);
  test.PushBack(4);
  EXPECT_FALSE(test.Empty());
  EXPECT_EQ(test.Size(), 4);
  EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
  test.PushBack(5);
  EXPECT_THAT(test.GetData(), ElementsAre(2, 3, 4, 5));
  test.PushBack(6);
  EXPECT_THAT(test.GetData(), ElementsAre(3, 4, 5, 6));
  test.PushBack(7);
  EXPECT_THAT(test.GetData(), ElementsAre(4, 5, 6, 7));
  test.PushBack(8);
  EXPECT_THAT(test.GetData(), ElementsAre(5, 6, 7, 8));
}

TEST(CyclicVectorTest, CyclicVectorWithZeroMaxSize) {
  CyclicVector<int> test(0);
  EXPECT_TRUE(test.Empty());
  EXPECT_EQ(test.Size(), 0);
  EXPECT_EQ(test.GetMaxSize(), 0);
  test.PushBack(1);
  EXPECT_TRUE(test.Empty());
  EXPECT_EQ(test.Size(), 0);
  test.Shift(1000);
  EXPECT_TRUE(test.Empty());
  EXPECT_EQ(test.Size(), 0);
}

TEST(CyclicVectorTest, ChangingMaxSizeAfterCreation) {
  CyclicVector<int> test(4);
  test.PushBack(1);
  test.PushBack(2);
  test.PushBack(3);
  test.PushBack(4);
  EXPECT_EQ(test.GetMaxSize(), 4);
  EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
  test.SetMaxSize(4);
  EXPECT_EQ(test.GetMaxSize(), 4);
  EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
  test.SetMaxSize(6);
  EXPECT_EQ(test.GetMaxSize(), 6);
  EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3, 4));
  test.PushBack(5);
  test.PushBack(6);
  test.PushBack(7);
  EXPECT_THAT(test.GetData(), ElementsAre(2, 3, 4, 5, 6, 7));
  test.SetMaxSize(4);
  EXPECT_EQ(test.GetMaxSize(), 4);
  EXPECT_THAT(test.Size(), 4);
  EXPECT_THAT(test.GetData(), ElementsAre(4, 5, 6, 7));
  test.SetMaxSize(0);
  EXPECT_TRUE(test.Empty());
  EXPECT_EQ(test.Size(), 0);
  EXPECT_EQ(test.GetMaxSize(), 0);
}

TEST(CyclicVectorTest, DecreasingMaxSizeInNotFullVector) {
  {
    CyclicVector<int> test(5);
    test.PushBack(1);
    test.PushBack(2);
    test.PushBack(3);
    test.PushBack(4);
    test.SetMaxSize(2);
    EXPECT_THAT(test.GetData(), ElementsAre(3, 4));
  }
  {
    CyclicVector<int> test(5);
    test.PushBack(1);
    test.PushBack(2);
    test.PushBack(3);
    test.SetMaxSize(4);
    EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3));
    test.SetMaxSize(3);
    EXPECT_THAT(test.GetData(), ElementsAre(1, 2, 3));
  }
}

TEST(CyclicVectorTest, DecreasingMaxSizeInEmptyVector) {
  CyclicVector<int> test(12);
  EXPECT_TRUE(test.Empty());
  EXPECT_EQ(test.Size(), 0);
  EXPECT_EQ(test.GetMaxSize(), 12);
  test.SetMaxSize(5);
  EXPECT_TRUE(test.Empty());
  EXPECT_EQ(test.Size(), 0);
  EXPECT_EQ(test.GetMaxSize(), 5);
}

TEST(CyclicVectorTest, MixCommandCalls) {
  CyclicVector<int> test(4);
  test.PushBack(1);
  test.PushBack(2);
  test.Shift(-1);
  EXPECT_THAT(test.GetData(), ElementsAre(2, 1));
  test.PushBack(3);
  test.Shift(2);
  EXPECT_THAT(test.GetData(), ElementsAre(1, 3, 2));
  test.PushBack(4);
  EXPECT_THAT(test.GetData(), ElementsAre(1, 3, 2, 4));
  test.PushBack(5);
  test.SetMaxSize(6);
  test.PushBack(6);
  test.Shift(-3);
  test.PushBack(7);
  EXPECT_THAT(test.GetData(), ElementsAre(5, 6, 3, 2, 4, 7));
}

TEST(CyclicVectorTest, OverfillingBeginIndex) {
  CyclicVector<int> test(2);
  test.PushBack(1);
  test.PushBack(2);
  test.Shift(-1);
  test.Shift(-1);
  test.Shift(-1);
  EXPECT_THAT(test.GetData(), ElementsAre(2, 1));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
