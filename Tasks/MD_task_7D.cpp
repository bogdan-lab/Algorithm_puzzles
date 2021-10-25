#include <algorithm>
#include <iostream>
#include <limits>
#include <optional>
#include <queue>
#include <sstream>
#include <vector>

class RangeTree {
  static constexpr int64_t EMPTY_VALUE = std::numeric_limits<int64_t>::min();
  static constexpr int64_t INFINITY = std::numeric_limits<int64_t>::max();

 public:
  RangeTree(const std::vector<int64_t>& elements) {
    size_t pow2 = GetClosestRightPow2(elements.size());
    data_.resize(2 * pow2 - 1);
    size_t j = 0;
    for (size_t i = pow2 - 1; i < data_.size(); ++i, ++j) {
      data_[i] = Node();
      data_[i].start = j;
      data_[i].end = j;
      if (j < elements.size()) {
        data_[i].min_val = elements[j];
      }
    }
    int idx = data_.size() - 1;
    while (idx > 0) {
      data_[Parent(idx)] = MergeNodes(data_[idx - 1], data_[idx]);
      idx -= 2;
    }
  }

  void Set(size_t start, size_t end, int64_t val) {
    SetImpl(0, start, end, val);
  }

  void Add(size_t start, size_t end, int64_t val) {
    AddImpl(0, start, end, val);
  }

  int64_t Min(size_t start, size_t end) { return MinImpl(0, start, end); }

 private:
  struct Node {
    int64_t min_val = INFINITY;
    size_t start = 0;
    size_t end = 0;
    int64_t set_val = EMPTY_VALUE;
    int64_t add_val = 0;
  };

  int64_t GetMinVal(size_t idx) const {
    if (data_[idx].set_val != EMPTY_VALUE) {
      return data_[idx].set_val + data_[idx].add_val;
    }
    return data_[idx].min_val + data_[idx].add_val;
  }

  int64_t MinImpl(size_t head_idx, size_t start, size_t end) {
    PushModification(head_idx);
    if (data_[head_idx].end < start || data_[head_idx].start > end) {
      return INFINITY;
    }
    if (data_[head_idx].end <= end && data_[head_idx].start >= start) {
      return GetMinVal(head_idx);
    }
    return std::min(MinImpl(Left(head_idx), start, end),
                    MinImpl(Right(head_idx), start, end));
  }

  void UpdateParent(size_t curr_idx) {
    if (curr_idx == 0) return;
    size_t p_idx = Parent(curr_idx);
    data_[p_idx].min_val =
        std::min(GetMinVal(Left(p_idx)), GetMinVal(Right(p_idx)));
    UpdateParent(p_idx);
  }

  void SetImpl(size_t head_idx, size_t start, size_t end, int64_t val) {
    PushModification(head_idx);
    if (data_[head_idx].end < start || data_[head_idx].start > end) {
      return;
    }
    if (data_[head_idx].end <= end && data_[head_idx].start >= start) {
      data_[head_idx].add_val = 0;
      data_[head_idx].set_val = val;
      UpdateParent(head_idx);
      return;
    }
    SetImpl(Left(head_idx), start, end, val);
    SetImpl(Right(head_idx), start, end, val);
  }

  void AddImpl(size_t head_idx, size_t start, size_t end, int64_t val) {
    PushModification(head_idx);
    if (data_[head_idx].end < start || data_[head_idx].start > end) {
      return;
    }
    if (data_[head_idx].end <= end && data_[head_idx].start >= start) {
      data_[head_idx].add_val += val;
      UpdateParent(head_idx);
      return;
    }
    AddImpl(Left(head_idx), start, end, val);
    AddImpl(Right(head_idx), start, end, val);
  }

  void Push(size_t from, size_t to) {
    if (data_[from].set_val != EMPTY_VALUE) {
      data_[to].add_val = 0;
      data_[to].set_val = data_[from].set_val;
    }
    data_[to].add_val += data_[from].add_val;
  }

  bool IsLeaf(size_t idx) const { return Left(idx) >= data_.size(); }

  void PushModification(size_t head_idx) {
    if (data_[head_idx].min_val == INFINITY) {
      data_[head_idx].set_val = EMPTY_VALUE;
      data_[head_idx].add_val = 0;
      return;
    }
    if (data_[head_idx].set_val != EMPTY_VALUE) {
      data_[head_idx].min_val = data_[head_idx].set_val;
    }
    data_[head_idx].min_val += data_[head_idx].add_val;

    if (!IsLeaf(head_idx)) {
      Push(head_idx, Left(head_idx));
      Push(head_idx, Right(head_idx));
    }
    data_[head_idx].set_val = EMPTY_VALUE;
    data_[head_idx].add_val = 0;
  }

  static Node MergeNodes(const Node& lhs, const Node& rhs) {
    Node res;
    res.min_val = std::min(lhs.min_val, rhs.min_val);
    res.start = std::min(lhs.start, rhs.start);
    res.end = std::max(lhs.end, rhs.end);
    return res;
  }

  static size_t GetClosestRightPow2(size_t input_size) {
    size_t res = 1;
    while (res < input_size) {
      res *= 2;
    }
    return res;
  }

  static size_t Left(size_t id) { return 2 * id + 1; }
  static size_t Right(size_t id) { return 2 * (id + 1); }
  static size_t Parent(size_t id) { return (id - 1) / 2; }

  std::vector<Node> data_;
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
  size_t n;
  input >> n;
  std::vector<int64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }
  RangeTree rtree(data);
  std::string command;
  size_t start;
  size_t end;
  while (input >> command >> start >> end) {
    if (command == "min") {
      std::cout << rtree.Min(start - 1, end - 1) << '\n';
    } else if (command == "set") {
      int64_t val;
      input >> val;
      rtree.Set(start - 1, end - 1, val);
    } else {
      int64_t val;
      input >> val;
      rtree.Add(start - 1, end - 1, val);
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
1 2 3 4 5
min 2 5
min 1 5
min 1 4
min 2 4
set 1 3 10
add 2 4 4
min 2 5
min 1 5
min 1 4
min 2 4
)";
    Solution(ss);
    std::cout << "expected = 2;1;1;2;5;5;8;8\n";
  }
}
