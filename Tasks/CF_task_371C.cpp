#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

struct Stuff {
  uint64_t bread = 0;
  uint64_t sausage = 0;
  uint64_t cheese = 0;
};

void Solution(std::istream& input = std::cin);
void RunTests();
uint64_t MaxBurgerNum(const Stuff& burger, const Stuff& kitchen,
                      const Stuff& prices, uint64_t budget);

bool CheckIfCan(uint64_t num, const Stuff& burger, const Stuff& kitchen,
                const Stuff& prices, uint64_t budget);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  std::string recipe;
  input >> recipe;
  Stuff burger;
  for (const auto& el : recipe) {
    switch (el) {
      case 'B': {
        burger.bread++;
        break;
      }
      case 'S': {
        burger.sausage++;
        break;
      }
      default: {
        burger.cheese++;
        break;
      }
    }
  }
  Stuff kitchen;
  input >> kitchen.bread >> kitchen.sausage >> kitchen.cheese;
  Stuff prices;
  input >> prices.bread >> prices.sausage >> prices.cheese;
  uint64_t budget;
  input >> budget;
  std::cout << MaxBurgerNum(burger, kitchen, prices, budget) << '\n';
}

uint64_t MaxBurgerNum(const Stuff& burger, const Stuff& kitchen,
                      const Stuff& prices, uint64_t budget) {
  uint64_t lhs = 0;
  uint64_t rhs =
      std::max({kitchen.bread, kitchen.sausage, kitchen.cheese}) + budget + 1;
  while (rhs - lhs > 1) {
    uint64_t mid = (rhs + lhs) / 2;
    if (CheckIfCan(mid, burger, kitchen, prices, budget)) {
      lhs = mid;
    } else {
      rhs = mid;
    }
  }
  return lhs;
}

bool CheckIfCan(uint64_t num, const Stuff& burger, const Stuff& kitchen,
                const Stuff& prices, uint64_t budget) {
  auto subtract = [](uint64_t lhs, uint64_t rhs) {
    return rhs >= lhs ? 0 : lhs - rhs;
  };
  Stuff needed;
  needed.bread = subtract(num * burger.bread, kitchen.bread);
  needed.sausage = subtract(num * burger.sausage, kitchen.sausage);
  needed.cheese = subtract(num * burger.cheese, kitchen.cheese);
  return budget >= needed.bread * prices.bread +
                       needed.sausage * prices.sausage +
                       needed.cheese * prices.cheese;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(BBBSSC
6 4 1
1 2 3
4
)";
    Solution(ss);
    std::cout << "expected = 2\n";
  }
  {
    std::stringstream ss;
    ss << R"(BBC
1 10 1
1 10 1
21
)";
    Solution(ss);
    std::cout << "expected = 7\n";
  }
  {
    std::stringstream ss;
    ss << R"(BSC
1 1 1
1 1 3
1000000000000
)";
    Solution(ss);
    std::cout << "expected = 200000000001\n";
  }
}
