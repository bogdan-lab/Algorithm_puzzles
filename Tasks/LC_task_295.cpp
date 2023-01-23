#include <functional>
#include <queue>

using MaxHeap = std::priority_queue<int, std::vector<int>, std::less<int>>;
using MinHeap = std::priority_queue<int, std::vector<int>, std::greater<int>>;

constexpr int kMinValue = -1'000'000;
constexpr int kMaxValue = 1'000'000;

class MedianFinder {
 public:
  MedianFinder() {
    lhs_.push(kMinValue);
    rhs_.push(kMaxValue);
  }

  void addNum(int num) {
    if (num > rhs_.top()) {
      rhs_.push(num);
    } else {
      lhs_.push(num);
    }
    BallanceHeaps();
  }

  double findMedian() {
    if (lhs_.size() > rhs_.size()) {
      return lhs_.top();
    }
    return (lhs_.top() + rhs_.top()) / 2.0;
  }

 private:
  void BallanceHeaps() {
    while (lhs_.size() > rhs_.size() && lhs_.size() - rhs_.size() > 1) {
      rhs_.push(lhs_.top());
      lhs_.pop();
    }

    while (rhs_.size() > lhs_.size()) {
      lhs_.push(rhs_.top());
      rhs_.pop();
    }
  }

  MaxHeap lhs_;
  MinHeap rhs_;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
