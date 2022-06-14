#include <algorithm>
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

constexpr int kDaySize = 1440;

void Solution(std::istream& input = std::cin);
void RunTests();
int CalcPalindrom(const std::string& time, int step);
bool IsPalindrom(int time);

std::vector<int> GeneratePossibleTimes(int start, int step);

int TimeToMinutes(const std::string& time);
int CharToInt(char ch) { return static_cast<int>(ch) - static_cast<int>('0'); }

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

void Solution(std::istream& input) {
  int t;
  input >> t;
  while (t--) {
    std::string time;
    int step;
    input >> time >> step;
    std::cout << CalcPalindrom(time, step) << '\n';
  }
}

int TimeToMinutes(const std::string& time) {
  int hour = CharToInt(time[0]) * 10 + CharToInt(time[1]);
  int minutes = CharToInt(time[3]) * 10 + CharToInt(time[4]);
  return 60 * hour + minutes;
}

std::vector<int> GeneratePossibleTimes(int start, int step) {
  std::vector<int> result;
  std::array<int, kDaySize> lookup_table;
  std::fill(lookup_table.begin(), lookup_table.end(), 0);
  while (true) {
    if (lookup_table[start]) break;
    result.push_back(start);
    lookup_table[start] = 1;
    start = (start + step) % kDaySize;
  }
  return result;
}

int CalcPalindrom(const std::string& time, int step) {
  int start_offset = TimeToMinutes(time);
  std::vector<int> possible_times = GeneratePossibleTimes(start_offset, step);
  int count =
      std::count_if(possible_times.begin(), possible_times.end(), IsPalindrom);
  return count;
}

bool IsPalindrom(int time) {
  int minutes = time % 60;
  int hours = time / 60;
  int m_dec = minutes / 10;
  int m_rem = minutes % 10;
  int h_dec = hours / 10;
  int h_rem = hours % 10;
  return h_dec == m_rem && h_rem == m_dec;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(6
03:12 360
00:00 1
13:22 2
15:15 10
11:11 1440
22:30 27
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
