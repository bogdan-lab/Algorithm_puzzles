#include <algorithm>
#include <cassert>
#include <limits>
#include <stack>
#include <string>
#include <vector>

constexpr size_t kEmptyValue = std::numeric_limits<size_t>::max();
constexpr int kEmptyLength = std::numeric_limits<int>::min();

// Result will contain end index for valid bracets substring starting in i-th
// position. If kEmptyValue is stored in i-th position, then there is no correct
// bracet surface starting from it
std::vector<size_t> CreateChainVector(std::string_view str) {
  std::vector<size_t> result(str.size(), kEmptyValue);

  std::stack<size_t> pos_buff;
  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == '(') {
      pos_buff.push(i);
    } else {
      if (!pos_buff.empty()) {
        result[pos_buff.top()] = i + 1;
        pos_buff.pop();
      }
    }
  }
  return result;
}

int GetChainLen(const std::vector<size_t>& chain, size_t i,
                std::vector<int>& memo) {
  if (i >= memo.size()) return 0;
  if (memo[i] == kEmptyLength) {
    if (chain[i] == kEmptyValue) {
      memo[i] = 0;
    } else {
      memo[i] = chain[i] - i + GetChainLen(chain, chain[i], memo);
    }
  }
  return memo[i];
}

class Solution {
 public:
  int longestValidParentheses(std::string s) {
    if (s.empty()) return 0;
    std::vector<size_t> chain = CreateChainVector(s);
    std::vector<int> memo(s.size(), kEmptyLength);
    int max_len = std::numeric_limits<int>::min();
    for (size_t i = 0; i < chain.size(); ++i) {
      max_len = std::max(max_len, GetChainLen(chain, i, memo));
    }
    return max_len;
  }
};

int main() {
  Solution test;
  assert(test.longestValidParentheses("(()") == 2);
  assert(test.longestValidParentheses(")()())") == 4);
  assert(test.longestValidParentheses("") == 0);
  assert(test.longestValidParentheses("()(()") == 2);
  return 0;
}
