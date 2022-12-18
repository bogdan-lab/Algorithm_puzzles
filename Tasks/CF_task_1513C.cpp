#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

constexpr int kMod = 1'000'000'000 + 7;
constexpr int kMaxM = 2 * 100'000;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  // building dp
  std::vector<int> dp(kMaxM + 1 + 10);
  dp[0] = 1;
  std::vector<int> curr_val(1);
  std::vector<int> buff;
  for (int i = 1; i < dp.size(); ++i) {
    for (int v = 0; v < curr_val.size(); ++v) {
      ++curr_val[v];
      if (curr_val[v] < 10) {
        buff.push_back(curr_val[v]);
      } else {
        buff.push_back(1);
        buff.push_back(0);
      }
    }
    curr_val.clear();
    std::swap(curr_val, buff);
    dp[i] = curr_val.size();
  }

  while (n--) {
    int val, m;
    input >> val >> m;

    int res = 0;
    while (val) {
      int residual = val % 10;
      val -= residual;
      val /= 10;
      res += dp[residual + m];
      res %= kMod;
    }
    std::cout << res << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
1912 1
5 6
999 1
88 2
12 100
)";
    Solution(ss);
    std::cout << "expected = 5; 2; 6; 4; 2115\n";
  }
}
