#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int64_t GetGCD(int64_t a, int64_t b);
int64_t GetNumberCount(int64_t lcm, int64_t b, int64_t l , int64_t r);

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  //RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int64_t t;
  input >> t;
  while (t--) {
    int64_t a, b, q;
    input >> a >> b >> q;
    if(a > b){
      std::swap(a, b);
    }
    int64_t lcm = (a*b)/GetGCD(a, b);
    std::vector<int64_t> answer;
    answer.reserve(q);
    while (q--) {
      int64_t l, r;
      input >> l >> r;
      answer.push_back(GetNumberCount(lcm, b, l, r));
    }
    for (const auto& el : answer) {
      std::cout << el << ' ';
    }
    std::cout << '\n';
  }
}

int64_t GetGCD(int64_t a, int64_t b){
  while(b != 0){
    int64_t t = b;
    b = a % b;
    a = t;
  }
  return a;
}


int64_t GetNumberCount(int64_t lcm, int64_t b, int64_t l , int64_t r){
  if(r < b || b == lcm) return 0;
  l = std::max(b, l);
  int64_t lcm_before_l = l/lcm;
  // Check if l is inside lcm range
  int64_t l_lcm_range_start = lcm_before_l*lcm;
  int64_t l_lcm_range_end = l_lcm_range_start + b - 1;
  if(l <= l_lcm_range_end){
    l = l_lcm_range_end + 1;
  }
  // Synchronizing right edge
  int64_t r_lcm_range_start = (r/lcm)*lcm;
  int64_t r_lcm_range_end = r_lcm_range_start + b - 1;
  if(r <= r_lcm_range_end){
    r = r_lcm_range_start - 1;
  }
  // Entire query was inside lcm range
  if(l>r) return 0;
  
  int64_t lcm_inside_range = r/lcm - l/lcm;
  return r - l + 1 - lcm_inside_range*b;
}


void RunTests() {
  {
    std::stringstream ss;
    ss << R"(2
4 6 5
1 1
1 3
1 5
1 7
1 9
7 10 2
7 8
100 200
)";
    Solution(ss);
    std::cout << "expected = 0 0 0 2 4 || 0 91\n";
  }
  { // lcm is on the right edge
    std::stringstream ss;
    ss << R"(1
    4 6 1
    8 12)";
    Solution(ss);
    std::cout << "expected = 4\n";
  }
  { // Different crossections with the last range
    std::stringstream ss;
    ss << R"(1
    4 6 4
    8 13
    8 14
    8 17
    8 18)";
    Solution(ss);
    std::cout << "expected = 4 4 4 5\n";
  }
  { // Case when our range is inside some lcm range
    std::stringstream ss;
    ss << R"(1
    4 6 1
    13 16)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
  { // Different crossections with the first range
    std::stringstream ss;
    ss << R"(1
    4 6 4
    12 18
    14 18
    15 20
    17 19)";
    Solution(ss);
    std::cout << "expected = 1 1 3 2\n";
  }
  { // Start and end inside lcm range
    std::stringstream ss;
    ss << R"(1
    4 6 8
    12 24
    17 24
    12 29
    17 29
    14 25
    12 30
    17 30
    14 30)";
    Solution(ss);
    std::cout << "expected = 6 6 6 6 6 7 7 7\n";
  }
  { // Edge case for a, b
    std::stringstream ss;
    ss << R"(1
    1 1 2
    4 6
    17 24)";
    Solution(ss);
    std::cout << "expected = 0 0\n";
  }
  { // Edge case for a, b 2
    std::stringstream ss;
    ss << R"(1
    200 200 3
    300 500
    100 400
    17 24)";
    Solution(ss);
    std::cout << "expected = 0 0 0\n";
  }
  { // Edge case for a, b 3
    std::stringstream ss;
    ss << R"(1
    1 5 3
    300 500
    3 8
    17 24)";
    Solution(ss);
    std::cout << "expected = 0 0 0\n";
  }

}
