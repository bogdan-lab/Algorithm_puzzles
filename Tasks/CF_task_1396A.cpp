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

void Solution(std::istream& input) {
  int64_t n;
  input >> n;
  std::vector<int64_t> data(n);
  for (auto& el : data) {
    input >> el;
  }
  if (n == 1) {
    std::cout << "1 1\n";
    std::cout << data.front() << '\n';
    data.front() *= 2;

    std::cout << "1 1\n";
    std::cout << data.front() << '\n';
    data.front() *= 2;

    std::cout << "1 1\n";
    std::cout << -1 * data.front() << '\n';
    data.front() = 0;
    return;
  }
  std::cout << "1 " << n - 1 << '\n';
  for (int i = 0; i < n - 1; ++i) {
    int64_t fut_res = data[i] % n;
    if (fut_res <= 0) fut_res += n;
    int64_t add = (n - 1) * fut_res;
    std::cout << add << ' ';
    data[i] += add;
  }
  std::cout << '\n';

  std::cout << "1 " << n << '\n';
  for (int i = 0; i < n - 1; ++i) {
    std::cout << -1 * data[i] << ' ';
    data[i] = 0;
  }
  std::cout << n << '\n';
  data.back() += n;

  std::cout << n << ' ' << n << '\n';
  std::cout << -1 * data.back() << '\n';
  data.back() = 0;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
1 3 2 4
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
