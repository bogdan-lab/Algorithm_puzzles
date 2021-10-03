#include <cctype>
#include <iostream>
#include <new>
#include <sstream>
#include <string>

template <typename T>
class Vector {
 public:
  Vector() {
    capacity_ = 1;
    data_ = new T[capacity_];
  }

  void PushBack(T elem) {
    if (size_ == capacity_) {
      Realloc(CAPACITY_MULTIPLIER * capacity_);
    }
    data_[size_] = elem;
    ++size_;
  }

  void PopBack() {
    --size_;
    if (size_ == capacity_ / SHRINK_MULTIPLIER) {
      Realloc(capacity_ / CAPACITY_MULTIPLIER);
    }
  }

  bool Empty() const { return size_ == 0; }

  size_t Size() const { return size_; }

  const T& Back() const { return data_[size_ - 1]; }

  const T& operator[](size_t idx) const { return data_[idx]; }

  ~Vector() { delete[] data_; }

 private:
  void Realloc(size_t new_capacity) {
    T* old_data = data_;
    capacity_ = new_capacity;
    data_ = new T[capacity_];
    for (size_t i = 0; i < size_; ++i) {
      data_[i] = old_data[i];
    }
    delete[] old_data;
  }

  T* data_ = nullptr;
  size_t capacity_ = 0;
  size_t size_ = 0;

  static constexpr size_t CAPACITY_MULTIPLIER = 2;
  static constexpr size_t SHRINK_MULTIPLIER = 2 * CAPACITY_MULTIPLIER;
};

template <typename T>
class Stack {
 public:
  Stack() = default;

  void Push(const T& op) { data_.PushBack(op); }

  void Pop() { data_.PopBack(); }

  const T& Top() const { return data_.Back(); }

  bool Empty() const { return data_.Empty(); }

 private:
  Vector<T> data_;
};

void Solution(std::istream& input = std::cin);
int EvaluateExpressioin(const Vector<std::string>& elements);
bool IsNumber(const std::string& str);
int Compute(int lhs, int rhs, const std::string& operation);
void RunTests();

int main() {
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  std::string value;
  Vector<std::string> data;
  while (input >> value) {
    data.PushBack(value);
  }

  std::cout << EvaluateExpressioin(data) << '\n';
}

int EvaluateExpressioin(const Vector<std::string>& elements) {
  Stack<int> operation_stack;
  for (size_t i = 0; i < elements.Size(); ++i) {
    if (IsNumber(elements[i])) {
      operation_stack.Push(std::stoi(elements[i]));
    } else {
      int rhs = operation_stack.Top();
      operation_stack.Pop();
      int lhs = operation_stack.Top();
      operation_stack.Pop();
      operation_stack.Push(Compute(lhs, rhs, elements[i]));
    }
  }
  return operation_stack.Top();
}

int Compute(int lhs, int rhs, const std::string& operation) {
  if (operation == "+") return lhs + rhs;
  if (operation == "-") return lhs - rhs;
  if (operation == "*") return lhs * rhs;
  throw;
}

bool IsNumber(const std::string& str) {
  if (str.size() > 1) return true;
  if (str.empty()) return false;
  return std::isdigit(str[0]);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(8 9 + 1 7 - *
)";
    Solution(ss);
    std::cout << "expected = -102\n";
  }
}
