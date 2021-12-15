#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();
std::vector<uint64_t> GCD(std::vector<uint64_t> data);
uint64_t GCD(uint64_t lhs, uint64_t rhs);
uint64_t GetGoodNumber(const std::vector<uint64_t>& data);
bool CheckVal(uint64_t val, const std::vector<uint64_t>& data);
uint64_t GCDForSequence(std::vector<uint64_t> data);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t = 0;
  input >> t;
  std::vector<uint64_t> data;
  while (t--) {
    int n = 0;
    input >> n;
    while (n--) {
      uint64_t val = 0;
      input >> val;
      data.push_back(val);
    }
    std::cout << GetGoodNumber(data) << '\n';
    data.clear();
  }
}

std::vector<uint64_t> GCD(std::vector<uint64_t> data) {
  std::vector<uint64_t> result;
  result.reserve(data.size() / 2 + 1);
  while (data.size() > 1) {
    uint64_t lhs = data.back();
    data.pop_back();
    uint64_t rhs = data.back();
    data.pop_back();
    result.push_back(GCD(lhs, rhs));
  }
  if (!data.empty()) {
    result.push_back(data.front());
  }
  return result;
}

uint64_t GCD(uint64_t lhs, uint64_t rhs) {
  while (lhs && rhs) {
    if (lhs > rhs) {
      lhs %= rhs;
    } else {
      rhs %= lhs;
    }
  }
  return std::max(lhs, rhs);
}

uint64_t GCDForSequence(std::vector<uint64_t> data) {
  while (data.size() > 1) {
    data = GCD(std::move(data));
  }
  return data.front();
}

bool CheckVal(uint64_t val, const std::vector<uint64_t>& data) {
  for (const auto& el : data) {
    if (!(el % val)) {
      return false;
    }
  }
  return true;
}

uint64_t GetGoodNumber(const std::vector<uint64_t>& data) {
  std::vector<uint64_t> odd;
  std::vector<uint64_t> even;
  odd.reserve(data.size() / 2 + 1);
  even.reserve(data.size() / 2 + 1);
  for (size_t i = 0; i < data.size(); ++i) {
    if ((i + 1) % 2) {
      odd.push_back(data[i]);
    } else {
      even.push_back(data[i]);
    }
  }

  uint64_t odd_val = GCDForSequence(odd);
  if (CheckVal(odd_val, even)) {
    return odd_val;
  }
  uint64_t even_val = GCDForSequence(even);
  if (CheckVal(even_val, odd)) {
    return even_val;
  }
  return 0;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(5
5
1 2 3 4 5
3
10 5 15
3
100 10 200
10
9 8 2 6 6 2 8 6 5 4
2
1 3
)";
    Solution(ss);
    std::cout << "expected 2; 0; 100; 0; 3\n";
  }
}
