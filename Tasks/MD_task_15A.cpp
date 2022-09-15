#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

using Lexem = std::variant<char, long long>;

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  std::vector<Lexem> res;

  bool is_expression_start = true;
  std::string number;

  auto store_number = [&number, &res]() {
    if (!number.empty()) {
      res.push_back(Lexem(std::atoll(number.c_str())));
      number.clear();
    }
  };

  while (true) {
    char c;
    input >> c;
    switch (c) {
      case '.': {
        store_number();
        break;
      }
      case '(': {
        store_number();
        is_expression_start = true;
        res.push_back(c);
        break;
      }
      case ')': {
        store_number();
        is_expression_start = false;
        res.push_back(c);
        break;
      }
      case '+': {
        store_number();
        if (!is_expression_start) {
          res.push_back(c);
        }
        is_expression_start = false;
        break;
      }
      case '-': {
        if (is_expression_start) {
          // we are about to read negative number
          number.push_back(c);
        } else {
          store_number();
          res.push_back(c);
        }
        is_expression_start = false;
        break;
      }
      case '*': {
        store_number();
        res.push_back(c);
        is_expression_start = false;
        break;
      }
      default: {
        // case with number
        number.push_back(c);
        is_expression_start = false;
        break;
      }
    }
    if (c == '.') break;
  }

  for (const auto& el : res) {
    std::visit([](const auto& val) { std::cout << val << '\n'; }, el);
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(1+(2*2-3).
)";
    Solution(ss);
    std::cout << "input = 1+(2*2-3)\n";
  }
  {
    std::stringstream ss;
    ss << R"(-1+(-2023*1232-3).
)";
    Solution(ss);
    std::cout << "input = -1+(-2023*1232-3)\n";
  }
}
