#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <string>
#include <vector>

std::string Convert(const std::vector<int>& data);
std::vector<int> BuildFactorials(int n);
int SetElement(int pos, std::vector<int>& data, int k,
               const std::vector<int>& factorials);
char ToChar(int val);

class Solution {
 public:
  std::string getPermutation(int n, int k) {
    --k;  // because the 1st permutation means nothis should be changed
    std::vector<int> data(n);
    std::iota(data.begin(), data.end(), 1);
    std::vector<int> factorials = BuildFactorials(n);
    for (int pos = 0; pos < data.size(); ++pos) {
      k -= SetElement(pos, data, k, factorials);
    }
    return Convert(data);
  }
};

std::string Convert(const std::vector<int>& data) {
  std::string result;
  result.reserve(data.size());
  std::transform(data.begin(), data.end(), std::back_inserter(result), ToChar);
  return result;
}

std::vector<int> BuildFactorials(int n) {
  std::vector<int> result(n + 1);
  result[0] = 1;
  for (int i = 1; i <= n; ++i) {
    result[i] = result[i - 1] * i;
  }
  return result;
}

int SetElement(int pos, std::vector<int>& data, int k,
               const std::vector<int>& factorials) {
  int curr_fac = factorials[data.size() - pos - 1];
  int shift = k / curr_fac;
  auto begin = data.begin() + pos;
  std::rotate(begin, begin + shift, begin + shift + 1);
  return shift * curr_fac;
}

char ToChar(int val) { return static_cast<char>(val + static_cast<int>('0')); }

int main() {
  Solution sol;
  std::string res = sol.getPermutation(4, 9);
  std::cout << res << std::endl;
  return 0;
}