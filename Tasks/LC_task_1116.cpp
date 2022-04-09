#include <condition_variable>
#include <functional>
#include <mutex>

class ZeroEvenOdd {
 private:
  enum class Status { kPrintZero, kPrintEven, kPrintOdd };

  std::condition_variable cv_;
  std::mutex m_;
  const int last_num_ = 0;
  int prev_val = 0;
  Status status = Status::kPrintZero;

  bool TaskIsFinished() { return prev_val == last_num_; }

 public:
  ZeroEvenOdd(int n) : last_num_(n) {}

  // printNumber(x) outputs "x", where x is an integer.
  void zero(function<void(int)> printNumber) {
    while (true) {
      std::unique_lock<std::mutex> lock(m_);
      cv_.wait(lock, [this]() {
        return status == Status::kPrintZero || TaskIsFinished();
      });
      if (TaskIsFinished()) break;
      printNumber(0);
      status = prev_val % 2 ? Status::kPrintEven : Status::kPrintOdd;
      lock.unlock();
      cv_.notify_all();
    }
  }

  void even(function<void(int)> printNumber) {
    while (true) {
      std::unique_lock<std::mutex> lock(m_);
      cv_.wait(lock, [this]() {
        return status == Status::kPrintEven || TaskIsFinished();
      });
      if (TaskIsFinished()) break;
      printNumber(++prev_val);
      status = Status::kPrintZero;
      lock.unlock();
      cv_.notify_all();
    }
  }

  void odd(function<void(int)> printNumber) {
    while (true) {
      std::unique_lock<std::mutex> lock(m_);
      cv_.wait(lock, [this]() {
        return status == Status::kPrintOdd || TaskIsFinished();
      });
      if (TaskIsFinished()) break;
      printNumber(++prev_val);
      status = Status::kPrintZero;
      lock.unlock();
      cv_.notify_all();
    }
  }
};
