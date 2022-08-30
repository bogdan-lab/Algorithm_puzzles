#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void Solution(std::istream& input = std::cin);
void RunTests();

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  // RunTests();
  Solution(std::cin);
  return 0;
}

std::vector<int> CountPoints(const std::vector<std::string>& p1,
                             const std::vector<std::string>& p2,
                             const std::vector<std::string>& p3) {
  std::vector<int> count(3);

  auto it1 = p1.begin();
  auto it2 = p2.begin();
  auto it3 = p3.begin();

  while (it1 != p1.end() && it2 != p2.end() && it3 != p3.end()) {
    if (*it1 < *it2 && *it1 < *it3) {
      count[0] += 3;
      ++it1;
      continue;
    }
    if (*it2 < *it1 && *it2 < *it3) {
      count[1] += 3;
      ++it2;
      continue;
    }
    if (*it3 < *it1 && *it3 < *it2) {
      count[2] += 3;
      ++it3;
      continue;
    }

    if (*it1 == *it2 && *it1 < *it3) {
      count[0] += 1;
      count[1] += 1;
      ++it1;
      ++it2;
      continue;
    }
    if (*it1 < *it2 && *it1 == *it3) {
      count[0] += 1;
      count[2] += 1;
      ++it1;
      ++it3;
      continue;
    }
    if (*it2 == *it3 && *it2 < *it1) {
      count[1] += 1;
      count[2] += 1;
      ++it2;
      ++it3;
      continue;
    }

    if (*it1 == *it2 && *it1 == *it3) {
      ++it1;
      ++it2;
      ++it3;
      continue;
    }
  }

  return count;
}

void Solution(std::istream& input) {
  int case_num;
  input >> case_num;
  std::string infinite_word = "zzzz";
  while (case_num--) {
    int word_num;
    input >> word_num;
    std::vector<std::string> p1(word_num + 1);
    for (int i = 0; i < word_num; ++i) {
      input >> p1[i];
    }
    p1[word_num] = infinite_word;
    std::vector<std::string> p2(word_num + 1);
    for (int i = 0; i < word_num; ++i) {
      input >> p2[i];
    }
    p2[word_num] = infinite_word;
    std::vector<std::string> p3(word_num + 1);
    for (int i = 0; i < word_num; ++i) {
      input >> p3[i];
    }
    p3[word_num] = infinite_word;

    std::sort(p1.begin(), p1.end());
    std::sort(p2.begin(), p2.end());
    std::sort(p3.begin(), p3.end());
    std::vector<int> count = CountPoints(p1, p2, p3);
    std::cout << count[0] << ' ' << count[1] << ' ' << count[2] << '\n';
  }
}

void RunTests() {
  {
    std::stringstream ss;
    ss << R"(3
1
abc
def
abc
3
orz for qaq
qaq orz for
cod for ces
5
iat roc hem ica lly
bac ter iol ogi sts
bac roc lly iol iat
)";
    Solution(ss);
    std::cout << "expected = 0\n";
  }
}
