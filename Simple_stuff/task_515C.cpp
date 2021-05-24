#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

const char* expand(char ch) {
  switch (ch) {
    case '2':
      return "2";
    case '3':
      return "3";
    case '4':
      return "322";
    case '5':
      return "5";
    case '6':
      return "53";
    case '7':
      return "7";
    case '8':
      return "7222";
    case '9':
      return "7332";
  }
  return "BAD_CHAR";
}

int ctoi(char ch) { return static_cast<int>(ch) - static_cast<int>('0'); }

std::string get_x(const std::string& num) {
  std::string res;
  res.reserve(num.size() * 3);
  for (auto ch : num) {
    res.append(expand(ch));
  }
  std::sort(res.begin(), res.end(),
            [](char lhs, char rhs) { return ctoi(lhs) > ctoi(rhs); });
  return res;
}

std::string filter_num(const std::string& in) {
  std::string out;
  out.reserve(in.size());
  std::copy_if(in.begin(), in.end(), std::back_inserter(out),
               [](char el) { return el != '0' && el != '1'; });
  return out;
}

void solution(std::istream& input = std::cin) {
  size_t n;
  input >> n;
  std::string num;
  input >> num;
  std::cout << get_x(filter_num(num)) << '\n';
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
        1234
        )";
    solution(ss);
  }
  {
    std::stringstream ss;
    ss << R"(3
        555
        )";
    solution(ss);
  }
}

int main() {
  //RunTests();
  solution(std::cin);
  return 0;
}
