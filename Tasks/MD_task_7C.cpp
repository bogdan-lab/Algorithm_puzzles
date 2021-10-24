#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

class FenvikTree {
 public:
  FenvikTree(const std::vector<int64_t>& data)
      : data_(data.size()), sums_(data.size()) {
    for (int64_t i = 0; i < data_.size(); ++i) {
      Set(i, data[i]);
    }
  }

  void Set(int64_t i, int64_t val) { Add(i, val - data_[i]); }

  int64_t Sum(int64_t lhs, int64_t rhs) const {
    return lhs == 0 ? GetPrefixSum(rhs)
                    : GetPrefixSum(rhs) - GetPrefixSum(lhs - 1);
  }

 private:
  static int64_t F(int64_t i) { return i & (i + 1); }

  int64_t GetPrefixSum(int64_t idx) const {
    int64_t res = 0;
    while (idx >= 0) {
      res += sums_[idx];
      idx = F(idx) - 1;
    }
    return res;
  }

  void Add(int64_t i, int64_t val) {
    data_[i] += val;
    while (i < sums_.size()) {
      sums_[i] += val;
      i = i | (i + 1);
    }
  }

  std::vector<int64_t> data_;
  std::vector<int64_t> sums_;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int64_t n;
  input >> n;
  std::vector<int64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }
  FenvikTree ftree(data);
  std::string command;
  while (input >> command) {
    int64_t lhs, rhs;
    input >> lhs >> rhs;
    if (command == "sum") {
      std::cout << ftree.Sum(lhs - 1, rhs - 1) << '\n';
    } else {
      ftree.Set(lhs - 1, rhs);
    }
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
1 2 3 4 5
sum 2 5
sum 1 5
sum 1 4
sum 2 4
set 1 10
set 2 3
set 5 2
sum 2 5
sum 1 5
sum 1 4
sum 2 4)";
    Solution(ss);
    std::cout << "expected = 14; 15; 10; 9; 12; 22; 20; 10\n";
  }
}
