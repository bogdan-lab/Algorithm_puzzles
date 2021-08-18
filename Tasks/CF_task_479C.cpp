#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

size_t get_min_date(std::vector<std::pair<size_t, size_t>> dates) {
  std::sort(dates.begin(), dates.end(), [](auto lhs, auto rhs) {
    return lhs.first < rhs.first ||
           (lhs.first == rhs.first && lhs.second < rhs.second);
  });
  size_t min = 0;
  for (const auto& el : dates) {
    min = min <= el.second ? el.second : el.first;
  }
  return min;
}

void solution(std::istream& input = std::cin) {
  size_t n;
  input >> n;
  std::vector<std::pair<size_t, size_t>> dates;
  dates.reserve(n);
  while (n--) {
    size_t v1, v2;
    input >> v1 >> v2;
    dates.emplace_back(v1, v2);
  }
  std::cout << get_min_date(std::move(dates)) << '\n';
}

int main() {
  solution(std::cin);
  return 0;
}

