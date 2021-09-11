#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct King {
  std::string name;
  std::string str_num;
  size_t num = 0;
};

void solution(std::istream& input = std::cin);
void run_tests();
size_t convert_to_num(const std::string& str_num);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

size_t convert_to_num(const std::string& str_num) {
  size_t idx = 0;
  if (str_num[idx] == 'L') return 50;
  while (idx < str_num.size() && str_num[idx] == 'X') {
    ++idx;
  }
  size_t tens = idx;

  if (tens && idx < str_num.size() && str_num[idx] == 'L') {
    ++idx;
    tens = 4;
  }

  size_t ones = 0;
  while (idx < str_num.size() && str_num[idx] == 'I') {
    ++idx;
    ++ones;
  }

  if (ones) {
    if (idx < str_num.size() && str_num[idx] == 'V' && ones == 1) {
      return 10 * tens + 4;
    }

    if (idx < str_num.size() && str_num[idx] == 'X' && ones == 1) {
      return 10 * tens + 9;
    }

    return 10 * tens + ones;
  }

  while (idx < str_num.size()) {
    ones += str_num[idx++] == 'V' ? 5 : 1;
  }

  return 10 * tens + ones;
}

void solution(std::istream& input) {
  int n;
  input >> n;
  std::vector<King> data(n);
  for (auto& el : data) {
    input >> el.name >> el.str_num;
    el.num = convert_to_num(el.str_num);
  }

  std::sort(data.begin(), data.end(), [](const auto& lhs, const auto& rhs) {
    return lhs.name < rhs.name || (lhs.name == rhs.name && lhs.num < rhs.num);
  });

  for (const auto& el : data) {
    std::cout << el.name << ' ' << el.str_num << '\n';
  }
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(2
Luis IX
Luis VIII
)";
    solution(ss);
  }
  {
    std::stringstream ss;
    ss << R"(2
Luis IX
Philippe II
)";
    solution(ss);
  }
  {
    std::stringstream ss;
    ss << R"(2
Philippe II
Philip II
)";
    solution(ss);
  }
  {
    std::stringstream ss;
    ss << R"(2
Philip L
Philip XLVII
)";
    solution(ss);
  }
}
