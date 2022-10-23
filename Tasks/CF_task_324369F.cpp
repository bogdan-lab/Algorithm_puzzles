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

void Solution(std::istream& input) {
  int n, q;
  input >> n >> q;
  std::vector<int64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }

  std::vector<int> diff(data.size());
  while (q--) {
    int l, r;
    input >> l >> r;
    --l;
    ++diff[l];
    if (r < diff.size()) {
      --diff[r];
    }
  }

  std::vector<int64_t> count_pref(diff.size() + 1);
  for (int i = 1; i < count_pref.size(); ++i) {
    count_pref[i] = count_pref[i - 1] + diff[i - 1];
  }

  std::sort(count_pref.begin() + 1, count_pref.end());
  std::sort(data.begin(), data.end());
  int64_t res = 0;
  for (int i = 0; i < data.size(); ++i) {
    res += data[i] * count_pref[i + 1];
  }
  std::cout << res << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3 3
5 3 2
1 2
2 3
1 3
)";
    Solution(ss);
    std::cout << "expected = 25\n";
  }
  {
    std::stringstream ss;
    ss << R"(5 3
5 2 4 1 3
1 5
2 3
2 3
)";
    Solution(ss);
    std::cout << "expected = 33\n";
  }
}
