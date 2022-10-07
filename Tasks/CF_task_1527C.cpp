#include <algorithm>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

int64_t CalcWeight(const std::vector<int>& data) {
  std::vector<std::pair<int, int>> val_idx;
  val_idx.reserve(data.size());
  for (size_t i = 0; i < data.size(); ++i) {
    val_idx.push_back({data[i], i});
  }
  std::sort(val_idx.begin(), val_idx.end());

  int64_t count = 0;
  for (size_t i = 1; i < val_idx.size(); ++i) {
    if (val_idx[i].first != val_idx[i - 1].first) continue;
    int64_t idx_dist = val_idx[i].second - val_idx[i - 1].second;
    // take into account full windows
    int64_t max_w_full_size = std::min<int64_t>(
        val_idx[i].second, val_idx.size() - val_idx[i - 1].second + 1);
    int64_t full_w_count = max_w_full_size - 1;
    count += full_w_count * (1 + (max_w_full_size - 1)) / 2;
    // take into account partial windows
    int64_t f_val_after_max = data.size() - (max_w_full_size + 1) + 1;
    int64_t decr_count = f_val_after_max - 1;
    count += decr_count * (1 + f_val_after_max) / 2;
  }
  return count;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    int n;
    input >> n;
    std::vector<int> data(n);
    for (auto& el : data) {
      input >> el;
    }
    std::cout << CalcWeight(data) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(1
7
0 1 2 1 1 7 6
)";
    Solution(ss);
    std::cout << "expected = 6; 0\n";
  }
  {
    std::stringstream ss;
    ss << R"(2
4
1 2 1 1
4
1 2 3 4
)";
    Solution(ss);
    std::cout << "expected = 6; 0\n";
  }
}
