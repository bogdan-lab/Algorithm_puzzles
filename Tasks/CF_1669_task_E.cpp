#include <iostream>
#include <sstream>
#include <vector>

constexpr size_t kSize =
    static_cast<size_t>('k') - static_cast<size_t>('a') + 1;

struct StringCase {
  std::vector<int64_t> first_letter = std::vector<int64_t>(kSize);
  std::vector<int64_t> second_letter = std::vector<int64_t>(kSize);
  int64_t first_total = 0;
  int64_t second_total = 0;
};

size_t GetIndex(char ch) {
  return static_cast<size_t>(ch) - static_cast<size_t>('a');
}

int64_t GetDiffNumber(const std::vector<int64_t>& counts, int64_t total);

void Solution(std::istream& input = std::cin);
void RunTests();

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
    int n;
    input >> n;
    std::vector<StringCase> data(kSize);
    std::string str;
    while (n--) {
      input >> str;
      size_t fst = GetIndex(str[0]);
      size_t scd = GetIndex(str[1]);
      data[fst].first_letter[scd]++;
      data[fst].first_total++;
      data[scd].second_letter[fst]++;
      data[scd].second_total++;
    }
    int64_t result = 0;
    for (const auto& el : data) {
      result += GetDiffNumber(el.first_letter, el.first_total) +
                GetDiffNumber(el.second_letter, el.second_total);
    }
    std::cout << result << '\n';
  }
}

int64_t GetDiffNumber(const std::vector<int64_t>& counts, int64_t total) {
  int64_t result = 0;
  for (const auto& el : counts) {
    result += el * (total - el);
  }
  return result / 2;
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(4
6
ab
cb
db
aa
cc
ef
7
aa
bb
cc
ac
ca
bb
aa
4
kk
kk
ab
ab
5
jf
jf
jk
jk
jk
)";
    Solution(ss);
    std::cout << "expected = 5; 6; 0; 6\n";
  }
}
