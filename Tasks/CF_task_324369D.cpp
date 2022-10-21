#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct DPStruct {
  int64_t count = 0;
  int need_out = 0;
  int curr_in = 0;
};
int64_t GetCount(const std::vector<int>& data);

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

int64_t GetCount(const std::vector<int>& data) {
  std::vector<DPStruct> dp(data.size());

  for (int i = 0; i < data.size(); ++i) {
    dp[i].need_out = data[i] - 1;
    if (data[i] + i >= data.size()) {
      dp[i].count = data[i] - std::max<int>(data.size() - 1 - i, 1);
    }
  }

  if (data.size() == 1) return dp[0].count;

  for (int i = data.size() - 2; i >= 0; --i) {
    int64_t curr_c = 0;
    for (int j = 2; j <= data[i] - dp[i].count; ++j) {
      int s = i + j;
      if (dp[s].curr_in >= dp[s].need_out) {
        ++curr_c;
      } else {
        ++dp[s].curr_in;
      }
    }
    dp[i].count += dp[i + 1].count + curr_c;
  }
  return dp[0].count;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  std::vector<int> data;

  while (t--) {
    size_t n;
    input >> n;
    data.resize(n);
    for (auto& el : data) {
      input >> el;
    }

    int64_t res = GetCount(data);
    std::cout << res << '\n';
    data.clear();
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
7
1 4 2 2 2 2 2
2
2 3
5
1 1 1 1 1
4
1 9 2 1
1
6
)";
    Solution(ss);
    std::cout << "expected = 4; 3; 0; 9; 5\n";
  }
}
