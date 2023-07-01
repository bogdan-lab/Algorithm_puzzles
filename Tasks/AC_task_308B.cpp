#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

struct PriceData {
  std::unordered_map<std::string, int> data;
  int def_price = 0;
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

int CalcFood(const PriceData& data, const std::vector<std::string>& food) {
  int res = 0;
  for (const auto& el : food) {
    auto it = data.data.find(el);
    if (it == data.data.end()) {
      res += data.def_price;
    } else {
      res += it->second;
    }
  }
  return res;
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;

  std::vector<std::string> food(n);
  for (auto& el : food) {
    input >> el;
  }

  std::vector<std::string> names(m);
  for (auto& el : names) {
    input >> el;
  }

  PriceData data;
  input >> data.def_price;
  std::vector<int> prices(m);
  for (auto& el : prices) {
    input >> el;
  }

  for (size_t i = 0; i < prices.size(); ++i) {
    data.data[names[i]] = prices[i];
  }

  std::cout << CalcFood(data, food) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
