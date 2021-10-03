#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>

class Stack {
 public:
  Stack() = default;

  void Push(int value) {
    head_ = new Node(value, head_);
    if (value < min_value_) {
      min_value_ = value;
      count_min_ = 1;
    } else if (value == min_value_) {
      ++count_min_;
    }
  }

  void Pop() {
    Node* to_delete = head_;
    head_ = head_->next;
    if (count_min_ && to_delete->value == min_value_) --count_min_;
    delete to_delete;
  }

  int GetMinimum() {
    if (!count_min_) {
      UpdateMinValue();
    }
    return min_value_;
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

  void UpdateMinValue() {
    min_value_ = std::numeric_limits<int>::max();
    Node* curr_node = head_;
    while (curr_node != nullptr) {
      if (curr_node->value < min_value_) {
        min_value_ = curr_node->value;
        count_min_ = 1;
      } else if (curr_node->value == min_value_) {
        ++count_min_;
      }
      curr_node = curr_node->next;
    }
  }

  Node* head_ = nullptr;
  int min_value_ = std::numeric_limits<int>::max();
  size_t count_min_ = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
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

void RunTests() {
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
    Solution(ss);
    std::cout << "expected = -3 2 2\n";
  }
}
