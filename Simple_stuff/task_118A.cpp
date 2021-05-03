#include <cctype>
#include <iostream>
#include <sstream>
#include <string>

char convert_to_lower(char c) { return static_cast<char>(std::tolower(c)); }

bool check_consonant(char c) {
  // expect c to be in lower!
  switch (c) {
    case 'a':
    case 'o':
    case 'y':
    case 'e':
    case 'u':
    case 'i':
      return false;
    default:
      return true;
  }
}

std::string copy_with_modification(const std::string& in) {
  std::string out;
  out.reserve(2 * in.size());
  for (const auto el : in) {
    char tmp = convert_to_lower(el);
    if (check_consonant(tmp)) {
      out.push_back('.');
      out.push_back(tmp);
    }
  }
  return out;
}

void solution(std::istream& in_stream) {
  std::string input;
  input.reserve(100);
  in_stream >> input;
  std::cout << copy_with_modification(input);
}

int main() {
  /*
    {
      std::stringstream ss;
      ss << "tour";
      solution(ss);
      std::cout << '\n';
    }
    {
      std::stringstream ss;
      ss << "CodeForces";
      solution(ss);
      std::cout << '\n';
    }
    {
      std::stringstream ss;
      ss << "aBAcAba";
      solution(ss);
      std::cout << '\n';
    }
    */
  solution(std::cin);
  return 0;
}

