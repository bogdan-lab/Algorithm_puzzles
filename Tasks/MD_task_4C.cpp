#include <iostream>
#include <sstream>

template <typename T>
class Queue {
 public:
  Queue() {
    capacity_ = 1;
    data_ = new T[capacity_];
    begin_idx_ = 0;
    end_idx_ = 0;
  }

  void Push(T elem) {
    if (NextIndex() == begin_idx_) {
      Realloc(CAPACITY_MULTIPLIER * capacity_);
    }
    if (end_idx_ == capacity_) {
      data_[0] = elem;
      end_idx_ = 1;
    } else {
      data_[end_idx_] = elem;
      end_idx_ = NextIndex();
    }
  }

  const T& Front() const { return data_[begin_idx_]; }

  void Pop() { ++begin_idx_; }

  bool Empty() const { return end_idx_ == begin_idx_; }

  ~Queue() { delete[] data_; }

 private:
  void Realloc(size_t new_capacity) {
    T* old_data = data_;
    data_ = new T[new_capacity];
    size_t idx = 0;
    while (begin_idx_ != end_idx_) {
      data_[idx++] = old_data[begin_idx_];
      begin_idx_ = begin_idx_ < capacity_ ? begin_idx_ + 1 : 0;
    }
    capacity_ = new_capacity;
    begin_idx_ = 0;
    end_idx_ = idx;
    delete[] old_data;
  }

  size_t NextIndex() const { return end_idx_ == capacity_ ? 0 : end_idx_ + 1; }

  T* data_ = nullptr;
  size_t capacity_ = 0;
  size_t begin_idx_ = 0;
  size_t end_idx_ = 0;

  static constexpr size_t CAPACITY_MULTIPLIER = 2;
  static constexpr size_t SHRINK_MULTIPLIER = 2 * CAPACITY_MULTIPLIER;
};

void solution(std::istream& input = std::cin);
void run_tests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  int n;
  input >> n;
  Queue<int> queue;
  while (n--) {
    char ch;
    input >> ch;
    if (ch == '+') {
      int value;
      input >> value;
      queue.Push(value);
    } else {
      std::cout << queue.Front() << '\n';
      queue.Pop();
    }
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(10
+ 1
+ 10
+ 5
+ 6
+ 7
-
-
-
-
-
)";
    solution(ss);
    std::cout << "expected = 1 10 5 6 7\n";
  }
}
