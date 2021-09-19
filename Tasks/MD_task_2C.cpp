#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

void solution(std::istream& input = std::cin);
void run_tests();
std::vector<size_t> get_radix_permut(const std::vector<std::string>& data,
                                     size_t phase);
size_t shift_to_int(char ch);
std::vector<size_t> get_sorted_position_vec(
    const std::vector<std::string>& data, size_t digit);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

void solution(std::istream& input) {
  size_t n = 0;
  size_t m = 0;
  size_t phase = 0;
  input >> n >> m >> phase;
  std::vector<std::string> data(n);
  for (auto& el : data) {
    input >> el;
  }

  const std::vector<size_t> radix_permut = get_radix_permut(data, phase);

  for (const auto& idx : radix_permut) {
    std::cout << data[idx] << '\n';
  }
}

size_t shift_to_int(char ch) {
  return static_cast<size_t>(ch) - static_cast<size_t>('a');
}

std::vector<size_t> get_sorted_position_vec(
    const std::vector<std::string>& data, size_t digit) {
  std::vector<size_t> count(shift_to_int('z') + 1);
  for (const auto& el : data) {
    count[shift_to_int(el[digit])]++;
  }
  std::vector<size_t> positions(count.size());
  for (size_t i = 1; i < positions.size(); ++i) {
    positions[i] += positions[i - 1] + count[i - 1];
  }
  return positions;
}

std::vector<size_t> get_radix_permut(const std::vector<std::string>& data,
                                     size_t phase) {
  std::vector<size_t> current_permut(data.size());
  std::iota(current_permut.begin(), current_permut.end(), 0);
  size_t curr_phase = 0;
  while (curr_phase < phase) {
    const size_t digit = data.front().size() - curr_phase - 1;
    std::vector<size_t> positions = get_sorted_position_vec(data, digit);
    std::vector<size_t> new_permut(current_permut.size());
    for (const auto& index : current_permut) {
      const size_t val = shift_to_int(data[index][digit]);
      new_permut[positions[val]] = index;
      ++positions[val];
    }
    current_permut = new_permut;
    ++curr_phase;
  }
  return current_permut;
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(3 3 1
bbb
aba
baa
)";
    solution(ss);
    std::cout << R"(expected =
aba
baa
bbb
===
)";
  }
  {
    std::stringstream ss;
    ss << R"(3 3 2
bbb
aba
baa
===
)";
    solution(ss);
    std::cout << R"(expected = 
baa
aba
bbb
===
)";
  }
  {
    std::stringstream ss;
    ss << R"(3 3 3
bbb
aba
baa
)";
    solution(ss);
    std::cout << R"(expected = 
aba
baa
bbb
===
)";
  }
}
