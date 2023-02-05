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

std::vector<int> BuildIndexes(const std::vector<int>& data) {
  std::vector<int> res(data.size());
  for (int i = 0; i < data.size(); ++i) {
    res[data[i] - 1] = i;
  }
  return res;
}

std::vector<int> CountRotationResults(const std::vector<int>& ai,
                                      const std::vector<int>& bi) {
  std::vector<int> count(ai.size());
  for (int i = 0; i < ai.size(); ++i) {
    int v = bi[i] - ai[i];
    if (v < 0) {
      v += ai.size();
    }
    ++count[v];
  }
  return count;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<int> a(n);
  for (auto& el : a) {
    input >> el;
  }
  std::vector<int> b(n);
  for (auto& el : b) {
    input >> el;
  }

  std::vector<int> ai = BuildIndexes(a);
  std::vector<int> bi = BuildIndexes(b);

  std::vector<int> rot_res = CountRotationResults(ai, bi);
  std::cout << *std::max_element(rot_res.begin(), rot_res.end()) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
