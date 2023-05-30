#include <algorithm>
#include <cassert>
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

std::vector<int> DecomposeNumber(int val) {
  std::vector<int> res;
  res.reserve(6);
  while (val) {
    res.push_back(val % 10);
    val /= 10;
  }
  std::reverse(res.begin(), res.end());
  return res;
}

void RemoveFrontZeros(std::vector<int>& el) {
  auto it = std::find(el.begin(), el.end(), 1);
  assert(it != el.end());
  int skipped = it - el.begin();
  std::rotate(el.begin(), it, el.end());
  el.erase(el.end() - skipped, el.end());
}

void RemoveFrontZeros(std::vector<std::vector<int>>& data) {
  for (auto& el : data) {
    RemoveFrontZeros(el);
  }
}

std::vector<std::vector<int>> BuildBinaryComp(const std::vector<int>& data) {
  int max_val = *std::max_element(data.begin(), data.end());
  std::vector<std::vector<int>> res(max_val, std::vector<int>(data.size()));

  for (size_t i = 0; i < data.size(); ++i) {
    for (int j = 0; j < data[i]; ++j) {
      res[j][i] = 1;
    }
  }

  RemoveFrontZeros(res);

  return res;
}

void PrintAnswer(const std::vector<std::vector<int>>& data) {
  std::cout << data.size() << '\n';
  for (const auto& el : data) {
    for (const auto& v : el) {
      std::cout << v;
    }
    std::cout << ' ';
  }
  std::cout << '\n';
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> number = DecomposeNumber(n);
  std::vector<std::vector<int>> res = BuildBinaryComp(number);
  PrintAnswer(res);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
