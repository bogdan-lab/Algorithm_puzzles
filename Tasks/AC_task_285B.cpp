#include <iostream>
#include <sstream>
#include <string>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

int GetMaxL(const std::string& data, int i) {
  int max_l = 0;
  for (int j = 0; j < data.size() - i; ++j) {
    if (data[j] != data[j + i]) {
      ++max_l;
    } else {
      break;
    }
  }
  return max_l;
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  std::string data;
  input >> data;

  for (int i = 1; i < data.size(); ++i) {
    std::cout << GetMaxL(data, i) << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
