#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct ValueIndex {
  uint64_t value;
  size_t index;
};

struct Answer {
  std::vector<size_t> positions;
};

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

std::vector<ValueIndex> BuildValAndPos(const std::vector<uint64_t>& data) {
  std::vector<ValueIndex> res;
  res.reserve(data.size());
  for (size_t i = 0; i < data.size(); ++i) {
    res.push_back({data[i], i});
  }
  return res;
}

std::vector<uint64_t> BuildPrefixSum(const std::vector<uint64_t>& data) {
  std::vector<uint64_t> res;
  res.reserve(data.size());
  res.push_back(data.front());
  for (size_t i = 1; i < data.size(); ++i) {
    res.push_back(res.back() + data[i]);
  }
  return res;
}

void SortData(std::vector<uint64_t>& data, std::vector<ValueIndex>& vi) {
  std::sort(data.begin(), data.end());
  std::sort(vi.begin(), vi.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.value < rhs.value;
  });
}

void PrintAnswer(const Answer& res) {
  std::cout << res.positions.size() << '\n';
  for (const auto& el : res.positions) {
    std::cout << el + 1 << ' ';
  }
  std::cout << '\n';
}

uint64_t GetLeftSum(const std::vector<uint64_t>& prefix, size_t index) {
  return prefix[index];
}

Answer CalcAnswer(const std::vector<ValueIndex>& vi,
                  const std::vector<uint64_t>& prefix) {
  Answer res;
  uint64_t threshold = vi.back().value;
  res.positions.push_back(vi.back().index);
  if (vi.size() == 1) return res;
  for (int i = vi.size() - 2; i >= 0; --i) {
    if (vi[i].value == threshold) {
      res.positions.push_back(vi[i].index);
    } else if (GetLeftSum(prefix, i) >= threshold) {
      threshold = vi[i].value;
      res.positions.push_back(vi[i].index);
    } else {
      break;
    }
  }
  std::sort(res.positions.begin(), res.positions.end());
  return res;
}

void SolveOne(std::istream& input) {
  int n;
  input >> n;
  std::vector<uint64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }

  auto val_and_pos = BuildValAndPos(data);
  SortData(data, val_and_pos);
  auto prefix_sum = BuildPrefixSum(data);
  Answer ans = CalcAnswer(val_and_pos, prefix_sum);
  PrintAnswer(ans);
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
