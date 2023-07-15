#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

struct Product {
  int price;
  std::vector<int> functions;
  std::vector<int8_t> count;
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

void MakeCount(Product& p, int m) {
  p.count.resize(m + 1);
  for (const auto& el : p.functions) {
    p.count[el] = 1;
  }
}

bool IsSubset(const Product& b, const Product& s) {
  for (const auto& el : s.functions) {
    if (b.count[el] == 0) {
      return false;
    }
  }
  return true;
}

bool Check(const std::vector<Product>& data, size_t i, size_t j) {
  if (data[j].price > data[i].price) {
    return false;
  }
  if (!IsSubset(data[j], data[i])) {
    return false;
  }
  if (!(data[i].price > data[j].price ||
        data[j].functions.size() > data[i].functions.size())) {
    return false;
  }
  return true;
}

void Solution(std::istream& input) {
  int n, m;
  input >> n >> m;

  std::vector<Product> data;
  data.reserve(n);
  while (n--) {
    data.emplace_back();
    auto& d = data.back();
    input >> d.price;
    int c;
    input >> c;
    d.functions.resize(c);
    for (auto& el : d.functions) {
      input >> el;
    }
    MakeCount(d, m);
  }

  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = 0; j < data.size(); ++j) {
      if (i == j) continue;
      if (Check(data, i, j)) {
        std::cout << "Yes\n";
        return;
      }
    }
  }
  std::cout << "No\n";
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
