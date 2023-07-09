#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Node {
  std::array<uint64_t, 3> count{0, 0, 0};
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

std::vector<Node> GetCount(const std::vector<int>& nums,
                           const std::string& word, char ch) {
  std::vector<Node> data(word.size());
  for (size_t i = 0; i < word.size(); ++i) {
    if (word[i] == ch) {
      data[i].count[nums[i]] = 1;
    }
  }
  return data;
}

std::vector<Node> BuildPrefix(const std::vector<int>& nums,
                              const std::string& word, char ch) {
  auto data = GetCount(nums, word, ch);

  std::vector<Node> prefix;
  prefix.reserve(word.size());
  prefix.push_back(data.front());
  for (size_t i = 1; i < data.size(); ++i) {
    prefix.emplace_back();
    for (size_t j = 0; j < data[i].count.size(); ++j) {
      prefix[i].count[j] = prefix[i - 1].count[j] + data[i].count[j];
    }
  }

  return prefix;
}

std::vector<Node> BuildSuffix(const std::vector<int>& nums,
                              const std::string& word, char ch) {
  auto data = GetCount(nums, word, ch);

  std::vector<Node> suffix(nums.size());
  suffix.back() = data.back();
  for (int i = suffix.size() - 2; i >= 0; --i) {
    for (int j = 0; j < data[i].count.size(); ++j) {
      suffix[i].count[j] = suffix[i + 1].count[j] + data[i].count[j];
    }
  }
  return suffix;
}

uint64_t GetNum(int m_val, int e_val, int x_val) {
  std::array<int, 4> lookup{};
  lookup[m_val] = 1;
  lookup[e_val] = 1;
  lookup[x_val] = 1;
  return std::find(lookup.begin(), lookup.end(), 0) - lookup.begin();
}

uint64_t GetNum(const std::array<uint64_t, 3>& m, int e_val,
                const std::array<uint64_t, 3>& x) {
  uint64_t res = 0;
  for (int i = 0; i < m.size(); ++i) {
    for (int j = 0; j < x.size(); ++j) {
      res += m[i] * x[j] * GetNum(i, e_val, j);
    }
  }
  return res;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> nums(n);
  for (auto& el : nums) {
    input >> el;
  }

  std::string word;
  input >> word;

  std::vector<Node> m_prefix = BuildPrefix(nums, word, 'M');
  std::vector<Node> x_suffix = BuildSuffix(nums, word, 'X');

  uint64_t total_count = 0;
  for (size_t i = 1; i < nums.size() - 1; ++i) {
    if (word[i] != 'E') continue;
    total_count += GetNum(m_prefix[i].count, nums[i], x_suffix[i].count);
  }

  std::cout << total_count << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
