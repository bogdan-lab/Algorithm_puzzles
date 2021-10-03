#include <algorithm>
#include <iostream>
#include <limits>
#include <optional>
#include <sstream>

class Stack {
 public:
  Stack() = default;

  void Push(int value) {
    Node* new_node = new Node(value, head_);
    head_ = new_node;
    if (min_value_) min_value_ = std::min(*min_value_, value);
  }

  void Pop() {
    Node* to_delete = head_;
    head_ = head_->next;
    delete to_delete;
    min_value_.reset();
  }

  int GetMinimum() {
    if (!min_value_) {
      CashMinValue();
    }
    return *min_value_;
  }

  ~Stack() {
    while (head_) {
      Node* next_node = head_->next;
      delete head_;
      head_ = next_node;
    }
  }

 private:
  struct Node {
    int value;
    Node* next;

    Node(int g_value, Node* g_next) : value(g_value), next(g_next) {}
  };

  void CashMinValue() {
    min_value_ = std::numeric_limits<int>::max();
    Node* curr_node = head_;
    while (curr_node != nullptr) {
      min_value_ = std::min(*min_value_, curr_node->value);
      curr_node = curr_node->next;
    }
  }

  Node* head_ = nullptr;
  std::optional<int> min_value_;
};

void solution(std::istream& input = std::cin);
void run_tests();

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  int n;
  input >> n;
  Stack my_stack;
  while (n--) {
    int id = 0;
    input >> id;
    switch (id) {
      case 1:
        int value;
        input >> value;
        my_stack.Push(value);
        break;
      case 2:
        my_stack.Pop();
        break;
      case 3:
        std::cout << my_stack.GetMinimum() << '\n';
        break;
      default:
        throw;
    }
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(8
1 2
1 3
1 -3
3
2
3
2
3
)";
    solution(ss);
    std::cout << "expected = -3 2 2\n";
  }
}
