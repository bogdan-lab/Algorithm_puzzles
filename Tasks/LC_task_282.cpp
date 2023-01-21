#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int ToInt(char c) { return static_cast<int>(c) - static_cast<int>('0'); }

void SetSignBefore(std::string& data, int i, char s) { data[2 * i - 1] = s; }

int64_t FillMultiplications(const std::string& str,
                            const std::vector<int>& mult, int& i,
                            std::string& curr_path) {
  int64_t val = ToInt(str[i]);
  while (i < str.size() - 1 && mult[i]) {
    val *= ToInt(str[i + 1]);
    SetSignBefore(curr_path, i + 1, '*');
    ++i;
  }
  return val;
}

void DFS(const std::string& str, int i, const std::vector<int>& mult,
         int64_t curr_val, int64_t target, std::string& curr_path,
         std::vector<std::string>& res) {
  if (i == str.size()) {
    if (curr_val == target) {
      res.push_back(curr_path);
    }
    return;
  }

  int init = i;
  int64_t val = FillMultiplications(str, mult, i, curr_path);

  // Try to add
  SetSignBefore(curr_path, init, '+');
  DFS(str, i + 1, mult, curr_val + val, target, curr_path, res);
  SetSignBefore(curr_path, init, ' ');
  // Try to subtract
  SetSignBefore(curr_path, init, '-');
  DFS(str, i + 1, mult, curr_val - val, target, curr_path, res);
  SetSignBefore(curr_path, init, ' ');
}

class Solution {
 public:
  std::vector<std::string> addOperators(std::string num, int target) {
    std::vector<std::string> res;
    std::string curr_path(2 * num.size() - 1, ' ');
    for (int i = 0; i < num.size(); ++i) {
      curr_path[2 * i] = num[i];
    }
    for (int count = 0; count < num.size(); ++count) {
      std::vector<int> mult(num.size() - 1);
      for (int i = mult.size() - count; i < mult.size(); ++i) {
        mult[i] = 1;
      }
      do {
        int i = 0;
        int64_t val = FillMultiplications(num, mult, i, curr_path);
        DFS(num, i + 1, mult, val, target, curr_path, res);
      } while (std::next_permutation(mult.begin(), mult.end()));
    }

    return res;
  }
};

int main() {
  {
    Solution s;
    std::vector<std::string> data = s.addOperators("232", 8);
    for (const auto& el : data) {
      std::cout << el << '\n';
    }
  }
  return 0;
}
