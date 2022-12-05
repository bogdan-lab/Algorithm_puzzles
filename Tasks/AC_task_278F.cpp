#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
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

uint32_t ToInt(char c) {
  return static_cast<uint32_t>(c) - static_cast<uint32_t>('a');
}

void Solution(std::istream& input) {
  uint32_t n;
  input >> n;
  std::vector<std::pair<uint32_t, uint32_t>> str_data(n);
  std::string str;
  for (auto& el : str_data) {
    input >> str;
    el.first = ToInt(str.front());
    el.second = ToInt(str.back());
  }
  std::vector<uint32_t> dp(1UL << n);
  for (uint32_t S = 1; S < dp.size(); ++S) {
    for (uint32_t c = 0; c < n; ++c) {
      if (S & (1 << c)) {
        // Here element c is inside set S

        uint32_t excluded_c = S ^ 1UL << c;
        uint32_t x = ~dp[excluded_c];
        // y == 1 if one cannot win after I use word c
        // y == 0 otherwise
        uint32_t y = 1UL & (~dp[excluded_c] >> str_data[c].second);
        // Here we set 1 if I can win by using word c
        dp[S] |= y << str_data[c].first;
      }
    }
  }
  std::cout << (dp.back() ? "First" : "Second") << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
enum
float
if
modint
takahashi
template
)";
    Solution(ss);
    std::cout << "expected = First\n";
  }
  {
    std::stringstream ss;
    ss << R"(10
catch
chokudai
class
continue
copy
exec
havoc
intrinsic
static
yucatec
)";
    Solution(ss);
    std::cout << "expected = Second\n";
  }
  {
    std::stringstream ss;
    ss << R"(16
mnofcmzsdx
lgeowlxuqm
ouimgdjxlo
jhwttcycwl
jbcuioqbsj
mdjfikdwix
jhvdpuxfil
peekycgxco
sbvxszools
xuuqebcrzp
jsciwvdqzl
obblxzjhco
ptobhnpfpo
muizaqtpgx
jtgjnbtzcl
sivwidaszs
)";
    Solution(ss);
    std::cout << "expected = First\n";
  }
}
