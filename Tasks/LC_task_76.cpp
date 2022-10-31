#include <cassert>
#include <string>
#include <utility>
#include <vector>

constexpr int ToInt(char c) {
  return static_cast<int>(c) - static_cast<int>('A');
}

constexpr int kAlphaSize = ToInt('z') + 1;

std::pair<int, int> FindNext(const std::string& s, const std::vector<int>& ref,
                             int& ref_count, std::vector<int>& buff,
                             std::pair<int, int> cur) {
  while (cur.second < s.size()) {
    int index = ToInt(s[cur.second]);
    if (ref[index]) {
      if (buff[index] < ref[index]) {
        --ref_count;
      }
      ++buff[index];
    }
    if (!ref_count) break;
    ++cur.second;
  }
  if (ref_count) return {cur.second + 1, cur.second};
  while (cur.first < s.size()) {
    int index = ToInt(s[cur.first]);
    if (ref[index]) {
      assert(buff[index] >= ref[index]);
      if (buff[index] == ref[index]) {
        break;
      }
      --buff[index];
    }
    ++cur.first;
  }
  return {cur.first, cur.second};
}

class Solution {
 public:
  std::string minWindow(std::string s, std::string t) {
    std::vector<int> ref(kAlphaSize);
    for (char c : t) {
      ++ref[ToInt(c)];
    }
    int ref_count = t.size();

    std::vector<int> buff(kAlphaSize);
    std::pair<int, int> res = FindNext(s, ref, ref_count, buff, {0, 0});
    if (res.first > res.second) return "";
    std::pair<int, int> min_size = res;
    while (res.second < s.size()) {
      int index = ToInt(s[res.first]);
      assert(ref[index]);
      --buff[index];
      ++ref_count;
      ++res.first;
      ++res.second;
      res = FindNext(s, ref, ref_count, buff, res);
      if (!ref_count && res.first < res.second &&
          res.second - res.first < min_size.second - min_size.first) {
        min_size = res;
      }
    }
    return s.substr(min_size.first, min_size.second - min_size.first + 1);
  }
};

int main() {
  Solution s;
  assert(s.minWindow("ADOBECODEBANC", "ABC") == "BANC");
  assert(s.minWindow("a", "a") == "a");
  assert(s.minWindow("", "a") == "");
  assert(s.minWindow("a", "") == "");
  return 0;
}
