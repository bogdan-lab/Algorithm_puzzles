#include <algorithm>
#include <iostream>
#include <sstream>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  RunTests();
  // Solution(std::cin);
  return 0;
}

uint32_t FindNextNonZeroBit(uint32_t val, uint32_t curr_bit) {
  while (curr_bit && !(curr_bit & val)) {
    curr_bit >>= 1;
  }
  return curr_bit;
}

int64_t Count(uint32_t a, uint32_t b, uint32_t curr_bit) {
  if (curr_bit == 0) return 0;
  uint32_t next_bit = curr_bit >> 1;
  uint32_t a_bit = a & curr_bit;
  uint32_t b_bit = b & curr_bit;
  if (a_bit == b_bit) {
    return Count(a % curr_bit, b % curr_bit, next_bit);
  }

  if (a_bit && !b_bit) {
    // shift b;
    uint32_t next = FindNextNonZeroBit(b, curr_bit);
    uint32_t diff = curr_bit - next;
    b += diff;
    return diff + Count(a % curr_bit, b % curr_bit, next_bit);
  } else {
    // do | or shift a
    uint32_t next = FindNextNonZeroBit(a, curr_bit);
    uint32_t diff = curr_bit - next;
    return std::min(diff + Count((a + diff) % curr_bit, b % curr_bit, next_bit),
                    1 + Count((a | b) % curr_bit, b % curr_bit, next_bit));
  }
}

void SolveOne(std::istream& input) {
  uint32_t a, b;
  input >> a >> b;

  std::cout << Count(a, b, 1U << 31U) << '\n';
}

void Solution(std::istream& input) {
  int n;
  input >> n;
  while (n--) SolveOne(input);
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
5 8
2 5
3 19
56678 164422
)";
    Solution(ss);
    std::cout << "expected = 1; 3; 2; 1; 23329\n";
  }
}
