#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <vector>

constexpr uint64_t kEmptyValue = std::numeric_limits<uint64_t>::max();

struct Prime {
  uint64_t val;
  uint64_t pow;
  uint64_t res;
};

struct Number {
  uint64_t val = 1;
  std::vector<Prime> details;
};

void Solution(std::istream& input = std::cin);
void RunTests();

std::vector<uint64_t> GetPrimeNumbers(uint64_t val);
std::vector<Number> GenerateNumbers(const std::vector<uint64_t>& primes,
                                    uint64_t limit);
Prime GetMaxPower(uint64_t prefix, uint64_t prime, uint64_t limit);

std::vector<Prime> FilterPrimes(const std::vector<Prime>& target,
                                const std::vector<Prime>& source);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  uint64_t n;
  input >> n;
  if (n == 1) {
    std::cout << 1 << '\n';
    return;
  }
  auto numbers = GenerateNumbers(GetPrimeNumbers(n), n);
  std::vector<Prime> lcm = numbers.back().details;
  lcm = FilterPrimes(lcm, numbers[numbers.size() - 2].details);
  lcm = FilterPrimes(lcm, numbers[numbers.size() - 3].details);
  uint64_t result = 1;
  for (const auto& el : lcm) {
    result *= el.res;
  }
  std::cout << result << '\n';
}

std::vector<uint64_t> GetPrimeNumbers(uint64_t val) {
  std::vector<uint64_t> all_numbers(val);
  std::iota(all_numbers.begin(), all_numbers.end(), 1);
  std::vector<uint64_t> result;
  for (size_t i = 1; i < all_numbers.size(); ++i) {
    if (all_numbers[i] != kEmptyValue) {
      result.push_back(all_numbers[i]);
    }
    for (size_t j = i; j < all_numbers.size(); j += i + 1) {
      all_numbers[j] = kEmptyValue;
    }
  }
  return result;
}

std::vector<Number> GenerateNumbers(const std::vector<uint64_t>& primes,
                                    uint64_t limit) {
  std::vector<Number> result;
  for (auto it = primes.rbegin(); it != primes.rend(); ++it) {
    Number tmp;
    for (auto in_it = it; in_it != primes.rend(); ++in_it) {
      Prime curr_prime = GetMaxPower(tmp.val, *in_it, limit);
      tmp.val *= curr_prime.res;
      tmp.details.push_back(std::move(curr_prime));
    }
    result.push_back(std::move(tmp));
  }
  std::sort(
      result.begin(), result.end(),
      [](const Number& lhs, const Number& rhs) { return lhs.val < rhs.val; });
  return result;
}

Prime GetMaxPower(uint64_t prefix, uint64_t prime, uint64_t limit) {
  uint64_t result = 1;
  uint64_t pow = 0;
  while (prefix * result * prime <= limit) {
    result *= prime;
    ++pow;
  }
  return {.val = prime, .pow = pow, .res = result};
}

std::vector<Prime> FilterPrimes(const std::vector<Prime>& target,
                                const std::vector<Prime>& source) {
  std::vector<Prime> result;
  auto tg = target.begin();
  auto sr = source.begin();
  while (sr != source.end() && tg != target.end()) {
    if (sr->val == tg->val) {
      result.push_back(sr->pow > tg->pow ? *sr : *tg);
      ++tg;
      ++sr;
      continue;
    }
    if (sr->val > tg->val) {
      result.push_back(*sr);
      ++sr;
      continue;
    }
    if (sr->val < tg->val) {
      result.push_back(*tg);
      ++tg;
      continue;
    }
  }
  auto fill_untill = [&](auto it, const std::vector<Prime>& vec) {
    while (it != vec.end()) {
      result.push_back(*it++);
    }
  };
  fill_untill(tg, target);
  fill_untill(sr, source);
  return result;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(9)";
    Solution(ss);
    std::cout << "expected = 504\n";
  }
  {
    std::stringstream ss;
    ss << R"(7)";
    Solution(ss);
    std::cout << "expected = 210\n";
  }
  {
    std::stringstream ss;
    ss << R"(1)";
    Solution(ss);
    std::cout << "expected = 1\n";
  }
  {
    std::stringstream ss;
    ss << R"(21)";
    Solution(ss);
    std::cout << "expected = 7980\n";
  }
}
