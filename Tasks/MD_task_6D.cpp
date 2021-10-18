#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class DPGrid {
 public:
  DPGrid(size_t row_num, size_t col_num) : substr_dist_(row_num) {
    for (auto& el : substr_dist_) {
      el.resize(col_num);
    }
  }

  size_t GetVal(int row, int col) const {
    if (row >= 0 && col >= 0) {
      return substr_dist_[row][col];
    }
    return std::max(row + 1, col + 1);
  }

  void SetVal(size_t row, size_t col, size_t val) {
    substr_dist_[row][col] = val;
  }

  size_t GetLast() const { return substr_dist_.back().back(); }

 private:
  std::vector<std::vector<size_t>> substr_dist_;
};

void Solution(std::istream& input = std::cin);
void RunTests();

size_t CalcDistance(const std::string& lhs, const std::string& rhs);

int main() {
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  std::string lhs;
  std::string rhs;
  input >> lhs >> rhs;
  std::cout << CalcDistance(lhs, rhs) << '\n';
}

size_t CalcDistance(const std::string& lhs, const std::string& rhs) {
  DPGrid dists(lhs.size(), rhs.size());
  for (int i = 0; i < lhs.size(); ++i) {
    for (int j = 0; j < rhs.size(); ++j) {
      if (lhs[i] == rhs[j]) {
        dists.SetVal(i, j, dists.GetVal(i - 1, j - 1));
      } else {
        size_t val = std::min({dists.GetVal(i - 1, j),      //
                               dists.GetVal(i - 1, j - 1),  //
                               dists.GetVal(i, j - 1)}      //
        );
        dists.SetVal(i, j, val + 1);
      }
    }
  }
  return dists.GetLast();
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(ABCDEFGH
ACDEXGIH
)";
    Solution(ss);
    std::cout << "expected = 3\n";
  }
}
