#include <iostream>
#include <sstream>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

bool IsPrime(int v) {
  for (int i = 2; i * i <= v; ++i) {
    if (!(v % i)) return false;
  }
  return true;
}

void SolveOne(std::istream& input) {
  int n;
  input >> n;

  if (n == 1) {
    std::cout << "FastestFinger\n";
    return;
  }

  if (n == 2) {
    std::cout << "Ashishgup\n";
    return;
  }

  if (n & 1) {
    std::cout << "Ashishgup\n";
    return;
  }

  int initial = n;

  while (!(n % 2)) {
    n /= 2;
  }

  int odd = n;
  int even = initial / odd;

  if (even > 2 && odd > 1) {
    std::cout << "Ashishgup\n";
  } else if (odd == 1) {
    std::cout << "FastestFinger\n";
  } else {
    // even == 2
    if (IsPrime(odd)) {
      std::cout << "FastestFinger\n";
    } else {
      std::cout << "Ashishgup\n";
    }
  }
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(7
1
2
3
4
5
6
12
)";
    Solution(ss);
    std::cout << "expected = F; A; A; F; A; F; A\n";
  }
}
