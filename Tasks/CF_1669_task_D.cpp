#include <iostream>
#include <sstream>
#include <string>

void Solution(std::istream& input = std::cin);
void RunTests();
bool CheckPainting(const std::string& target, std::string source);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t = 0;
  input >> t;
  while (t--) {
    int n = 0;
    input >> n;
    std::string target;
    input >> target;
    std::cout << (CheckPainting(target) ? "YES\n" : "NO\n");
  }
}

std::string Print(const std::string& str, const std::string& stamp,
                  size_t pos) {
  std::string res = str;
  res[pos] = stamp[0];
  res[pos + 1] = stamp[1];
  return res;
}

bool CheckPainting(const std::string& target, std::string source) {
  if (target == source) return true;
  bool result = false;
  for (size_t i = 0; i < target.size(); ++i) {
    if (target[i] != source[i]) {
      if (i == 0) {
        std::string lhs = Print(source, "BR", i);
        std::string rhs = Print(source, "RB", i);
        result =
            result || CheckPainting(target, lhs) || CheckPainting(target, rhs);
      } else if (i == target.size() - 1) {
        std::string lhs = Print(source, "BR", i - 1);
        std::string rhs = Print(source, "RB", i - 1);
        result =
            result || CheckPainting(target, lhs) || CheckPainting(target, rhs);
      } else {
        std::string lhs1 = Print(source, "BR", i);
        std::string lhs2 = Print(source, "BR", i - 1);
        std::string rhs1 = Print(source, "RB", i);
        std::string rhs2 = Print(source, "RB", i - 1);
        result = result || CheckPainting(target, lhs1) ||
                 CheckPainting(target, rhs1) || CheckPainting(target, lhs1) ||
                 CheckPainting(target, rhs2);
      }
    }
  }
  return result;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"()";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
