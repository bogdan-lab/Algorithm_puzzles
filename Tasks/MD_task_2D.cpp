#include <algorithm>
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
  auto sub_begin = teacher.begin();
  auto sub_end = teacher.begin();
  auto prev_end = teacher.begin();
  while (true) {
    sub_end = std::find_if(sub_end, teacher.end(), [&](char ch) {
      size_t ch_pos = shift_to_int(ch);
      if (teacher_count[ch_pos] + 1 > cards_count[ch_pos]) return true;
      teacher_count[ch_pos]++;
      return false;
    });

    count += get_substr_num(sub_end - sub_begin) -
             get_substr_num(prev_end - sub_begin);
    if (sub_end == teacher.end()) break;
    prev_end = sub_end;

    // skip characters absent in cards
    if (!cards_count[shift_to_int(*sub_end)]) {
      while (sub_begin != sub_end) {
        --teacher_count[shift_to_int(*sub_begin++)];
      }
      while (sub_end != teacher.end() && !cards_count[shift_to_int(*sub_end)]) {
        ++sub_end;
      }
      sub_begin = sub_end;
      prev_end = sub_end;
      continue;
    }

    sub_begin = std::find_if(sub_begin, sub_end, [&](char ch) {
      bool success = (ch == *sub_end);
      teacher_count[shift_to_int(ch)]--;
      return success;
    });
    if (sub_begin != sub_end) ++sub_begin;
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
  {
    std::stringstream ss;
    ss << R"(7 2
aaaaaaa
aa
)";
    solution(ss);
    std::cout << "expected = 13\n";
  }
  {
    std::stringstream ss;
    ss << R"(6 3
abczba
abc
)";
    solution(ss);
    std::cout << "expected = 9\n";
  }
  {
    std::stringstream ss;
    ss << R"(6 3
abcabz
abc
)";
    solution(ss);
    std::cout << "expected = 12\n";
  }
  {
    std::stringstream ss;
    ss << R"(6 3
zkfabc
abc
)";
    solution(ss);
    std::cout << "expected = 6\n";
  }
}
