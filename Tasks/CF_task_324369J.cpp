#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

constexpr int kMaxNum = 1'000'000;

void AddRange(std::vector<int64_t>& d, int s, int e) {
  ++d[s];
  if (e < d.size()) {
    --d[e];
  }
}

void Solution(std::istream& input) {
  int el_num, dl_num, ws;
  input >> el_num >> dl_num >> ws;
  std::vector<int> data(el_num);
  for (auto& el : data) {
    input >> el;
  }

  if (ws <= dl_num) {
    std::cout << kMaxNum - ws + 1 << '\n';
    return;
  }

  std::sort(data.begin(), data.end());
  std::vector<int64_t> diff(kMaxNum);

  int fill_num = ws - dl_num;
  for (int i = 0; i < data.size() - fill_num + 1; ++i) {
    int64_t dist = data[i + fill_num - 1] - data[i] + 1;
    if (dist <= ws) {
      int last_val = data[i + fill_num - 1];
      AddRange(diff, last_val, last_val + 1 + (ws - dist));
    }
  }

  std::vector<int64_t> p_diff(diff.size() + 1);
  for (int i = 1; i < p_diff.size(); ++i) {
    p_diff[i] = p_diff[i - 1] + diff[i - 1];
  }

  int count = std::count_if(p_diff.begin(), p_diff.end(),
                            [](int64_t v) { return v != 0; });
  std::cout << count << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(8 3 5
1 5 60 58 61 11 27 25
)";
    Solution(ss);
    std::cout << "expected = 9\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 3 3
    1 2 3 4 5)";
    Solution(ss);
    std::cout << "expected = 1'000'000-3+1\n";
  }
}
