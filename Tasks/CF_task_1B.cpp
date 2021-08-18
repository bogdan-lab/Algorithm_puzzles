#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

std::string to_excel(const std::string& str) {
  size_t c_pos = str.find('C', 2);
  int col = std::stoi(str.substr(c_pos + 1));
  std::string row = str.substr(1, c_pos - 1);

  auto to_char = [](int num) -> char {
    return static_cast<char>(num + static_cast<int>('A') - 1);
  };

  std::string col_name;
  do {
    int ch_num = col % 26;
    if (!ch_num) ch_num = 26;
    col_name.push_back(to_char(ch_num));
    col -= ch_num;
    col /= 26;
  } while (col);

  std::reverse(col_name.begin(), col_name.end());
  return col_name + row;
}

std::string from_excel(const std::string& str) {
  std::string res;
  size_t pos = 0;
  while (!std::isdigit(str[pos])) ++pos;
  std::string col_str = str.substr(0, pos);
  std::string row = str.substr(pos);
  auto to_int = [](char ch) -> int {
    return 1 + static_cast<int>(ch) - static_cast<int>('A');
  };
  std::reverse(col_str.begin(), col_str.end());
  int col = 0;
  int val = 1;
  for (size_t i = 0; i < col_str.size(); ++i) {
    col += val * to_int(col_str[i]);
    val *= 26;
  }
  return std::string("R") + row + std::string("C") + std::to_string(col);
}

bool check_NOT_excel(const std::string& str) {
  if (str.front() != 'R') {
    return false;
  }
  if (!std::isdigit(str[1])) {
    return false;
  }
  if (str.find('C', 2) == std::string::npos) {
    return false;
  }
  return true;
}

std::string translate(const std::string& str) {
  if (check_NOT_excel(str)) {
    return to_excel(str);
  }
  return from_excel(str);
}

void solution(std::istream& input = std::cin) {
  int n;
  input >> n;
  while (n--) {
    std::string str;
    input >> str;
    std::cout << translate(str) << '\n';
  }
}

void run_tests() {
  std::cout << "R23C55 -> " << to_excel("R23C55") << "=="
            << "BC23\n";
  std::cout << "R1C1 -> " << to_excel("R1C1") << "=="
            << "A1\n";
  std::cout << "R2C1 -> " << to_excel("R2C1") << "=="
            << "A2\n";
  std::cout << "R1C2 -> " << to_excel("R1C2") << "=="
            << "B1\n";
  std::cout << "R3C26 -> " << to_excel("R3C26") << "=="
            << "Z3\n";
  std::cout << "R4C52 -> " << to_excel("R4C52") << "=="
            << "AZ4\n";
  std::cout << "R98C688 -> " << to_excel("R98C688") << "=="
            << "ZL98\n";

  std::cout << "--------------------\n";
  std::cout << "BC23 -> " << from_excel("BC23") << "=="
            << "R23C55\n";
  std::cout << "AA5 -> " << from_excel("AA5") << "=="
            << "R5C27\n";
  std::cout << "AZ8 -> " << from_excel("AZ8") << "=="
            << "R8C52\n";
  std::cout << "A1 -> " << from_excel("A1") << "=="
            << "R1C1\n";
  std::cout << "A2 -> " << from_excel("A2") << "=="
            << "R2C1\n";
  std::cout << "B1 -> " << from_excel("B1") << "=="
            << "R1C2\n";
  std::cout << "Z3 -> " << from_excel("Z3") << "=="
            << "R3C26\n";
  std::cout << "--------------------\n";

  std::stringstream ss;
  ss << R"(2
      R23C55
      BC23
      )";
  solution(ss);
}

int main() {
  //run_tests();
  solution(std::cin);
  return 0;
}
