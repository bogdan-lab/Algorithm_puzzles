#include <algorithm>
#include <cassert>
#include <limits>
#include <stack>
#include <string>

void ClearStack(std::stack<size_t>& data) {
  std::stack<size_t> tmp;
  data.swap(tmp);
}

class Solution {
 public:
  int longestValidParentheses(std::string s) {
    if (s.empty()) return 0;
    std::stack<size_t> open_pos;
    int max_len = 0;
    size_t start_pos = s.find('(');
    size_t i = start_pos;
    // end points to the one after!
    size_t end_pos = start_pos;
    bool first_match_found = false;
    while (i < s.size()) {
      if (s[i] == '(') {
        open_pos.push(i++);
      } else {
        if (open_pos.empty()) {
          max_len = std::max<int>(max_len, end_pos - start_pos);
          start_pos = s.find('(', i);
          if (start_pos == std::string::npos) {
            return max_len;
          }
          ClearStack(open_pos);
          open_pos.push(start_pos);
          i = start_pos + 1;
          first_match_found = false;
        } else {
          start_pos = first_match_found ? std::min(start_pos, open_pos.top())
                                        : open_pos.top();
          end_pos = i + 1;
          open_pos.pop();
          i++;
          first_match_found = true;
        }
      }
    }
    return std::max<int>(max_len, end_pos - start_pos);
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
