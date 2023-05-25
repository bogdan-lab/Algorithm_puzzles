#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

using Graph = std::vector<std::vector<int>>;

struct Answer {
  explicit Answer(size_t size) : colors(size), max_color(0) {}
  std::vector<int> colors;
  int max_color;
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

std::vector<int> GetPrimeNumbers(int max_val, int count) {
  std::vector<int> res;
  res.reserve(count);
  std::vector<int> lookup(max_val + 1);
  lookup[0] = 1;
  lookup[1] = 1;
  for (int i = 2; i <= max_val; ++i) {
    if (lookup[i]) continue;
    res.push_back(i);
    if (res.size() == count) break;
    for (int j = 2 * i; j <= max_val; j += i) {
      lookup[j] = 1;
    }
  }
  return res;
}

Answer GetColors(const std::vector<int>& primes, const std::vector<int>& data) {
  Answer res(data.size());
  int curr_color = 1;
  for (int p = 0; p < primes.size(); ++p) {
    for (int i = 0; i < data.size(); ++i) {
      if (!res.colors[i] && (data[i] % primes[p]) == 0) {
        res.colors[i] = curr_color;
        res.max_color = curr_color;
      }
    }
    if (res.max_color == curr_color) {
      ++curr_color;
    }
  }
  return res;
}

void PrintAnswer(const Answer& ans) {
  std::cout << ans.max_color << '\n';
  for (const auto& el : ans.colors) {
    std::cout << el << ' ';
  }
  std::cout << '\n';
}

void SolveOne(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> data(n);
  for (auto& el : data) {
    input >> el;
  }
  Answer ans = GetColors(GetPrimeNumbers(1000, 11), data);
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
