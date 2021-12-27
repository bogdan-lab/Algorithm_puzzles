#include <algorithm>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

constexpr uint64_t kInfinity = std::numeric_limits<uint64_t>::max();

struct PriceData {
  uint64_t stable = 0;
  uint64_t rotated = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();

uint64_t CalcMinPrice(const std::vector<std::string>& data,
                      const std::vector<uint64_t>& prices);

uint64_t SafePlus(uint64_t val, uint64_t addition);

std::string Reverse(std::string str);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<uint64_t> prices(n);
  for (auto& el : prices) {
    input >> el;
  }
  std::vector<std::string> data(n);
  for (auto& el : data) {
    input >> el;
  }
  uint64_t result = CalcMinPrice(data, prices);
  if (result == kInfinity) {
    std::cout << "-1\n";
  } else {
    std::cout << result << '\n';
  }
}

uint64_t CalcMinPrice(const std::vector<std::string>& data,
                      const std::vector<uint64_t>& prices) {
  std::vector<PriceData> count(data.size());
  count[0].stable = 0;
  count[0].rotated = prices[0];
  std::string prev_reverse = Reverse(data[0]);
  for (size_t i = 1; i < data.size(); ++i) {
    std::string curr_reverse = Reverse(data[i]);
    uint64_t stable_to_stable =
        data[i] >= data[i - 1] ? count[i - 1].stable : kInfinity;
    uint64_t reverse_to_stable =
        data[i] >= prev_reverse ? count[i - 1].rotated : kInfinity;
    count[i].stable = std::min(stable_to_stable, reverse_to_stable);

    uint64_t stable_to_reverse = curr_reverse >= data[i - 1]
                                     ? SafePlus(count[i - 1].stable, prices[i])
                                     : kInfinity;
    uint64_t reverse_to_reverse =
        curr_reverse >= prev_reverse ? SafePlus(count[i - 1].rotated, prices[i])
                                     : kInfinity;
    count[i].rotated = std::min(stable_to_reverse, reverse_to_reverse);
    prev_reverse = curr_reverse;
  }
  return std::min(count.back().stable, count.back().rotated);
}

std::string Reverse(std::string str) {
  std::reverse(str.begin(), str.end());
  return str;
}

uint64_t SafePlus(uint64_t val, uint64_t addition) {
  return val == kInfinity ? kInfinity : val + addition;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
1 2
ba
ac
)";
    Solution(ss);
    std::cout << "expected = 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(3
1 3 1
aa
ba
ac
)";
    Solution(ss);
    std::cout << "expected = 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(2
5 5
bbb
aaa
)";
    Solution(ss);
    std::cout << "expected = -1\n";
  }
  {
    std::stringstream ss;
    ss << R"(2
3 3
aaa
aa
)";
    Solution(ss);
    std::cout << "expected = -1\n";
  }
}
