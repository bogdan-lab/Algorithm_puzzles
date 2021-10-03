#include <iostream>
#include <sstream>

template <typename T>
class Queue {
 public:
  Queue() {
    capacity_ = 2;
    data_ = new T[capacity_];
    begin_idx_ = 0;
    saving_pos_ = 0;
  }

  void Push(T elem) {
    if (NextSavingPos() == begin_idx_) {
      Realloc(CAPACITY_MULTIPLIER * capacity_);
    }
    data_[saving_pos_] = elem;
    saving_pos_ = NextSavingPos();
  }

  const T& Front() const { return data_[begin_idx_]; }

  void Pop() { ++begin_idx_; }

  ~Queue() { delete[] data_; }

 private:
  void Realloc(size_t new_capacity) {
    T* old_data = data_;
    data_ = new T[new_capacity];
    size_t idx = 0;
    while (begin_idx_ != saving_pos_) {
      data_[idx++] = old_data[begin_idx_];
      begin_idx_ = begin_idx_ < capacity_ ? begin_idx_ + 1 : 0;
    }
    capacity_ = new_capacity;
    begin_idx_ = 0;
    saving_pos_ = idx;
    delete[] old_data;
  }

  size_t NextSavingPos() const {
    return saving_pos_ + 1 == capacity_ ? 0 : saving_pos_ + 1;
  }

  T* data_ = nullptr;
  size_t capacity_ = 0;
  size_t begin_idx_ = 0;
  size_t saving_pos_ = 0;

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
