#include <algorithm>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>

struct Record {
  int order;
  int value;
};

class PriorityQueue {
 public:
  PriorityQueue() = default;

  void Push(int order, int value) {
    queue_.push_back(value);
    push_order_.push_back(order);
    MoveElementUp(queue_.size() - 1);
  }

  std::optional<Record> ExtractMin() {
    if (queue_.empty()) return std::nullopt;
    Record res{.order = push_order_.front(), .value = queue_.front()};
    Swap(0, queue_.size() - 1);
    PopBack();
    MoveElementDown(0);
    return res;
  }

  void DecreaseKey(int order, int new_value) {
    auto it = std::find(push_order_.begin(), push_order_.end(), order);
    if (it == push_order_.end()) return;
    size_t id = it - push_order_.begin();
    queue_[id] = new_value;
    MoveElementUp(id);
  }

 private:
  void Swap(size_t lhs_id, size_t rhs_id) {
    std::swap(queue_[lhs_id], queue_[rhs_id]);
    std::swap(push_order_[lhs_id], push_order_[rhs_id]);
  }
  void PopBack() {
    queue_.pop_back();
    push_order_.pop_back();
  }
  size_t Left(size_t id) { return 2 * id + 1; }
  size_t Right(size_t id) { return 2 * (id + 1); }
  size_t Parent(size_t id) { return (id - 1) / 2; }

  void MoveElementDown(size_t id) {
    while (true) {
      size_t min_id = id;
      size_t l_id = Left(id);
      if (l_id < queue_.size() && queue_[l_id] < queue_[min_id]) {
        min_id = l_id;
      }
      size_t r_id = Right(id);
      if (r_id < queue_.size() && queue_[r_id] < queue_[min_id]) {
        min_id = r_id;
      }
      if (min_id == id) break;
      Swap(min_id, id);
      id = min_id;
    }
  }

  void MoveElementUp(size_t id) {
    while (id && queue_[Parent(id)] > queue_[id]) {
      Swap(id, Parent(id));
      id = Parent(id);
    }
  }

  // element id = index in both vectors
  std::vector<int> queue_;
  std::vector<int> push_order_;
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
  std::string command;
  PriorityQueue prior_queue;
  int order = 0;
  while (input >> command) {
    ++order;
    if (command == "push") {
      int value;
      input >> value;
      prior_queue.Push(order, value);
    } else if (command == "extract-min") {
      std::optional<Record> min_rec = prior_queue.ExtractMin();
      if (min_rec) {
        std::cout << min_rec->value << ' ' << min_rec->order << '\n';
      } else {
        std::cout << "*\n";
      }
    } else {
      int order;
      int new_value;
      input >> order >> new_value;
      prior_queue.DecreaseKey(order, new_value);
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(push 3
push 4
push 2
extract-min
decrease-key 2 1
extract-min
extract-min
extract-min
)";
    Solution(ss);
    std::cout << "expected = 2 3; 1 2; 3 1; *\n";
  }
}
