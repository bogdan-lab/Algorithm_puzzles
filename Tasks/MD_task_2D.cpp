#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void solution(std::istream& input = std::cin);
void run_tests();
uint64_t count_substrings(const std::string& teacher, const std::string& cards);
std::vector<size_t> get_count_vector(const std::string& str);
size_t shift_to_int(char ch);
uint64_t get_substr_num(uint64_t max_str_size);

int main() {
  // run_tests();
  solution(std::cin);
  return 0;
}

uint64_t get_substr_num(uint64_t max_str_size) {
  return (1 + max_str_size) * max_str_size / 2;
}

size_t shift_to_int(char ch) {
  return static_cast<size_t>(ch) - static_cast<size_t>('a');
}

std::vector<size_t> get_count_vector(const std::string& str) {
  std::vector<size_t> res(shift_to_int('z') - shift_to_int('a') + 1);
  for (const auto& el : str) {
    res[shift_to_int(el)]++;
  }
  return res;
}

uint64_t count_substrings(const std::string& teacher,
                          const std::string& cards) {
  uint64_t count = 0;
  std::vector<size_t> cards_count = get_count_vector(cards);
  std::vector<size_t> teacher_count(shift_to_int('z') - shift_to_int('a') + 1);
  size_t l_idx = 0;
  size_t r_idx = 0;
  size_t prev_end = 0;
  while (true) {
    while (r_idx < teacher.size()) {
      size_t ch_pos = shift_to_int(teacher[r_idx]);
      if (teacher_count[ch_pos] + 1 <= cards_count[ch_pos]) {
        r_idx++;
        teacher_count[ch_pos]++;
      } else {
        break;
      }
    }
    count += get_substr_num(r_idx - l_idx) - get_substr_num(prev_end - l_idx);
    if (r_idx == teacher.size()) break;
    prev_end = r_idx;

    size_t bad_char = shift_to_int(teacher[r_idx]);
    while (l_idx < r_idx) {
      size_t ch_pos = shift_to_int(teacher[l_idx]);
      teacher_count[ch_pos]--;
      l_idx++;
      if (bad_char == ch_pos) break;
    }
  }
  return count;
}

void solution(std::istream& input) {
  int dummy;
  input >> dummy >> dummy;
  std::string teacher;
  std::string cards;
  input >> teacher >> cards;
  std::cout << count_substrings(teacher, cards) << '\n';
}

void run_tests() {
  {
    std::stringstream ss;
    ss << R"(4 3
aaab
aba
)";
    solution(ss);
    std::cout << "expected = 8\n";
  }
  {
    std::stringstream ss;
    ss << R"(7 3
abacaba
abc
)";
    solution(ss);
    std::cout << "expected = 15\n";
  }
}
